//=================================================================================================
// @file	Dx11VertexBuffer.cpp
//
// @date	2023-4-24
//=================================================================================================


#include "Dx11Primitive.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"
#include "../Fbx/FbxImportHelper.h"
#include <d3dcompiler.h>



//=================================================================================================
// @brief	 Construct
//=================================================================================================
Dx11Primitive::Dx11Primitive()
:
VertexShader ( nullptr ),
InputLayout  ( nullptr ),
VertexBuffer ( nullptr ),
IndexBuffer  ( nullptr )
{
    ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
    ZeroMemory( &IndexBufferDesc,  sizeof( D3D11_BUFFER_DESC ) );

    ZeroMemory( &IndexBufferSD, sizeof( D3D11_SUBRESOURCE_DATA ) );
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Primitive::Initialize()
{
    _createVertexShader();
}

//=================================================================================================
// @brief	Load FBX
//=================================================================================================
void Dx11Primitive::LoadFBX( const std::string& FilePath )
{
    FbxImportHelper fbxImportHelper;
    if ( !fbxImportHelper.Load( FilePath ) ) return;

    fbxImportHelper.GetVertices( Vertices, Indices );
    
    _createVertexBuffer();
    _createIndexBuffer ();
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Primitive::Render() const
{
    unsigned int stride = sizeof( Vertex );
    unsigned int offset = 0;

    GetDx11DeviceContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &stride, &offset );
    //GetDx11DeviceContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
    GetDx11DeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    GetDx11DeviceContext()->Draw( (unsigned int)( Vertices.size() ), 0 );
}

//=================================================================================================
// @brief	Create vertex shader
//=================================================================================================
void Dx11Primitive::_createVertexShader()
{
    ID3D10Blob* vs = Dx11ResourceFactory::CompileShader( L"../Shader/shader.hlsl", "VS", "vs_4_0" );
    if ( !vs ) return;

    GetDx11Device()->CreateVertexShader( vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &VertexShader );
    GetDx11DeviceContext()->VSSetShader( VertexShader, 0, 0 );

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    GetDx11Device()->CreateInputLayout( ied, sizeof( ied ) / sizeof( D3D11_INPUT_ELEMENT_DESC ), vs->GetBufferPointer(), vs->GetBufferSize(), &InputLayout );

    GetDx11DeviceContext()->IASetInputLayout( InputLayout );
}

//=================================================================================================
// @brief	Create vertex buffer
//=================================================================================================
void Dx11Primitive::_createVertexBuffer()
{
    if ( Vertices.empty() ) return;

    unsigned int bufferSize = sizeof( Vertex ) * Vertices.size();

    VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    VertexBufferDesc.ByteWidth = bufferSize;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    GetDx11Device()->CreateBuffer( &VertexBufferDesc, nullptr, &VertexBuffer );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, &Vertices[ 0 ], bufferSize );
    }
    GetDx11DeviceContext()->Unmap( VertexBuffer, 0 );
}

//=================================================================================================
// @brief	Create index buffer
//=================================================================================================
void Dx11Primitive::_createIndexBuffer()
{
    if ( Indices.empty() ) return;

    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.ByteWidth = (unsigned int)( sizeof( int ) * Indices.size() );
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    IndexBufferSD.pSysMem = &Indices[ 0 ];
    IndexBufferSD.SysMemPitch = 0;
    IndexBufferSD.SysMemSlicePitch = 0;

    GetDx11Device()->CreateBuffer( &IndexBufferDesc, &IndexBufferSD, &IndexBuffer );
}
