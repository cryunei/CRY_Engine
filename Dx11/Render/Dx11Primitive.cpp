//=================================================================================================
// @file	Dx11VertexBuffer.cpp
//
// @date	2023-4-24
//=================================================================================================


#include "Dx11Primitive.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ShaderFactory.h"
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
    _CreateVertexShader();
    _CreateVertexBuffer();
    _CreateIndexBuffer ();
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Primitive::Render() const
{
    unsigned int stride = sizeof( Vertex );
    unsigned int offset = 0;

    GetDx11DeviceContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &stride, &offset );
    GetDx11DeviceContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
    GetDx11DeviceContext()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    GetDx11DeviceContext()->DrawIndexed( (UINT)( Indices.size() ), 0, 0 );
}

//=================================================================================================
// @brief	Create vertex shader
//=================================================================================================
void Dx11Primitive::_CreateVertexShader()
{
    ID3D10Blob* vs = Dx11ShaderFactory::CompileShader( L"Shader/shader.hlsl", "VS", "vs_4_0" );
    if ( !vs ) return;

    GetDx11Device()->CreateVertexShader( vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &VertexShader );
    GetDx11DeviceContext()->VSSetShader( VertexShader, 0, 0 );

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    GetDx11Device()->CreateInputLayout( ied, sizeof( ied ) / sizeof( D3D11_INPUT_ELEMENT_DESC ), vs->GetBufferPointer(), vs->GetBufferSize(), &InputLayout );

    GetDx11DeviceContext()->IASetInputLayout( InputLayout );
}

//=================================================================================================
// @brief	Create vertex buffer
//=================================================================================================
void Dx11Primitive::_CreateVertexBuffer()
{
    Vertex Vertices[] =
    {
        { XMFLOAT3(  0.f, 0.f, 0.f ), XMFLOAT2( 0.f, 1.f ) },
        { XMFLOAT3(  0.f, 1.f, 0.f ), XMFLOAT2( 0.f, 0.f ) },
        { XMFLOAT3(  1.f, 0.f, 0.f ), XMFLOAT2( 1.f, 1.f ) },
        { XMFLOAT3(  1.f, 1.f, 0.f ), XMFLOAT2( 1.f, 0.f ) },
    };
    
    VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    VertexBufferDesc.ByteWidth = sizeof( Vertex ) * ( sizeof( Vertices ) / sizeof( Vertex ) );
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    GetDx11Device()->CreateBuffer( &VertexBufferDesc, nullptr, &VertexBuffer );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, Vertices, sizeof( Vertices ) );
    }
    GetDx11DeviceContext()->Unmap( VertexBuffer, 0 );
}

//=================================================================================================
// @brief	Create index buffer
//=================================================================================================
void Dx11Primitive::_CreateIndexBuffer()
{
    Indices = { 0, 1, 2, 1, 3, 2 };

    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.ByteWidth = (UINT)( sizeof( int ) * Indices.size() );
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    IndexBufferSD.pSysMem = &Indices[ 0 ];
    IndexBufferSD.SysMemPitch = 0;
    IndexBufferSD.SysMemSlicePitch = 0;

    GetDx11Device()->CreateBuffer( &IndexBufferDesc, &IndexBufferSD, &IndexBuffer );
}
