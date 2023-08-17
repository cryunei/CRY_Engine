#pragma once


class Dx11IndexBuffer;
class Dx11VertexBuffer;


//=====================================================================================================================
// @brief	Dx11Primitive
//=====================================================================================================================
class Dx11Primitive
{
private:
    Dx11VertexBuffer* VertexBuffer;
    Dx11IndexBuffer*  IndexBuffer;    

public:
    // Construct
    Dx11Primitive();

    // Initialize
    void Initialize( Dx11VertexBuffer* InVertexBuffer, Dx11IndexBuffer* InIndexBuffer );

    // Incrase render count
    void IncreaseRenderCount() const;

    // Decrease render count
    void DecreaseRenderCount() const;

    // Get vertex buffer
    const Dx11VertexBuffer* GetVertexBuffer() const { return VertexBuffer; }

    // Get index buffer
    const Dx11IndexBuffer* GetIndexBuffer() const { return IndexBuffer; }
};
