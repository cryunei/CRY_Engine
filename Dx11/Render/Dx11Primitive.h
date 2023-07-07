//=================================================================================================
// @file	Dx11VertexBuffer.h
//
// @brief	
//
// @date	2023-4-24
//=================================================================================================


#pragma once


#include "../DxTypes.h"


class Dx11Primitive
{
private:
    ID3D11VertexShader* VertexShader;
    ID3D11InputLayout*  InputLayout;

    ID3D11Buffer* VertexBuffer;
    ID3D11Buffer* IndexBuffer;

    std::vector< Vertex > Vertices;
    std::vector< int > Indices;

    D3D11_BUFFER_DESC VertexBufferDesc;
    D3D11_BUFFER_DESC IndexBufferDesc;

    D3D11_SUBRESOURCE_DATA IndexBufferSD;

public:
    // Construct
    Dx11Primitive();

    // Initialize
    void Initialize();

    // Load FBX
    void LoadFBX( const std::string& FilePath );

    // Render
    void Render() const;

private:
    // Create vertex shader
    void _createVertexShader();

    // Create vertex buffer
    void _createVertexBuffer();

    // Create index buffer
    void _createIndexBuffer();
};
