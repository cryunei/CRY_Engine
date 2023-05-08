//=================================================================================================
// @file	Dx11VertexBuffer.h
//
// @brief	
//
// @date	2023-4-24
//=================================================================================================


#pragma once


#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#pragma comment ( lib, "d3d11.lib" )


using namespace DirectX;


class Dx11Primitive
{
public:
    struct Vertex
    {
        XMFLOAT3 Position;  // position
        XMFLOAT2 TextureUV; // texture uv
    };

private:
    ID3D11VertexShader* VertexShader;
    ID3D11InputLayout*  InputLayout;

    ID3D11Buffer* VertexBuffer;
    ID3D11Buffer* IndexBuffer;

    std::vector< int > Indices;

    D3D11_BUFFER_DESC VertexBufferDesc;
    D3D11_BUFFER_DESC IndexBufferDesc;

    D3D11_SUBRESOURCE_DATA IndexBufferSD;

public:
    // Construct
    Dx11Primitive();

    // Initialize
    void Initialize( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Create buffers
    void CreateBuffers( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Render
    void Render( ID3D11DeviceContext* DeviceContext ) const;

private:
    // Create vertex shader
    void _CreateVertexShader( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Create vertex buffer
    void _CreateVertexBuffer( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Create index buffer
    void _CreateIndexBuffer( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );
};
