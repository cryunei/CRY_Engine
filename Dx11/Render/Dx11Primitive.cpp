//=================================================================================================
// @file	Dx11VertexBuffer.cpp
//
// @date	2023-4-24
//=================================================================================================


#include "Dx11Primitive.h"
#include <d3dcompiler.h>


//=================================================================================================
// @brief	 Construct
//=================================================================================================
Dx11Primitive::Dx11Primitive()
: VertexShader ( nullptr )
, VertexBuffer ( nullptr )
, IndexBuffer  ( nullptr )
{
    ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
    ZeroMemory( &IndexBufferDesc,  sizeof( D3D11_BUFFER_DESC ) );

    ZeroMemory( &IndexBufferSD, sizeof( D3D11_SUBRESOURCE_DATA ) );
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Primitive::Initialize( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    _CreateVertexShader( Device, DeviceContext );
    _CreateVertexShader( Device, DeviceContext );
    _CreateIndexBuffer ( Device, DeviceContext );
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Primitive::Render( ID3D11DeviceContext* DeviceContext ) const
{
    unsigned int stride = sizeof( Vertex );
    unsigned int offset = 0;

    DeviceContext->IASetVertexBuffers( 0, 1, &VertexBuffer, &stride, &offset );
    DeviceContext->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
    DeviceContext->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    DeviceContext->DrawIndexed( Indices.size(), 0, 0 );
}

//=================================================================================================
// @brief	Create vertex shader
//=================================================================================================
void Dx11Primitive::_CreateVertexShader( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    ID3D10Blob* vs    = nullptr;
    ID3D10Blob* error = nullptr;

    D3DCompileFromFile( L"Shader/shader.hlsl", nullptr, nullptr, "VS", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vs, &error );

    Device->CreateVertexShader( vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &VertexShader );

    DeviceContext->VSSetShader( VertexShader, 0, 0 );

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    Device->CreateInputLayout( ied, sizeof( ied ) / sizeof( D3D11_INPUT_ELEMENT_DESC ), vs->GetBufferPointer(), vs->GetBufferSize(), &InputLayout );

    DeviceContext->IASetInputLayout( InputLayout );
}

//=================================================================================================
// @brief	Create vertex buffer
//=================================================================================================
void Dx11Primitive::_CreateVertexBuffer( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    Vertex Vertices[] =
    {
        { XMFLOAT3(  0.0f,   0.5f, 0.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  0.45f, -0.5f, 0.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -0.45f, -0.5f, 0.0f ), XMFLOAT2( 0.0f, 1.0f ) },
        { XMFLOAT3(  0.0f,  -1.5f, 0.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    };

    VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    VertexBufferDesc.ByteWidth = sizeof( Vertex ) * ( sizeof( Vertices ) / sizeof( Vertex ) );
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    Device->CreateBuffer( &VertexBufferDesc, nullptr, &VertexBuffer );

    D3D11_MAPPED_SUBRESOURCE ms;
    DeviceContext->Map( VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, Vertices, sizeof( Vertices ) );
    }
    DeviceContext->Unmap( VertexBuffer, 0 );
}

//=================================================================================================
// @brief	Create index buffer
//=================================================================================================
void Dx11Primitive::_CreateIndexBuffer( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    Indices = { 0, 1, 2, 1, 3, 2 };

    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.ByteWidth = sizeof( int ) * Indices.size();
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    IndexBufferSD.pSysMem = &Indices[ 0 ];
    IndexBufferSD.SysMemPitch = 0;
    IndexBufferSD.SysMemSlicePitch = 0;

    Device->CreateBuffer( &IndexBufferDesc, &IndexBufferSD, &IndexBuffer );
}
