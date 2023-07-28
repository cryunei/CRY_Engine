//=================================================================================================
// @file	Dx11VertexBuffer.h
//
// @brief	
//
// @date	2023-4-24
//=================================================================================================


#pragma once


class Dx11VertexShader;
class Dx11IndexBuffer;
class Dx11VertexBuffer;


class Dx11Primitive
{
private:
    Dx11VertexBuffer* VertexBuffer;
    Dx11IndexBuffer*  IndexBuffer;
    Dx11VertexShader* VertexShader;    

public:
    // Construct
    Dx11Primitive();

    // Initialize
    void Initialize( Dx11VertexBuffer* InVertexBuffer, Dx11IndexBuffer* InIndexBuffer, Dx11VertexShader* InVertexShader );

    // Render
    void Render() const;
};
