#pragma once


#include "Dx11Resource.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11VertexBuffer
//=====================================================================================================================
class Dx11VertexBuffer : public Dx11Resource
{
private:
    struct ID3D11Buffer*     VertexBuffer;
    D3D11_BUFFER_DESC        VertexBufferDesc;
    unsigned int             VertexCount;
    unsigned int             Stride;
    unsigned int             Offset;
    D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;

public:
    // Construct
    Dx11VertexBuffer();
    Dx11VertexBuffer( const Dx11VertexBuffer& Other ) = default;
    Dx11VertexBuffer( Dx11VertexBuffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11VertexBuffer() = default;

    // Getters
    unsigned int GetCount() const { return VertexCount; }

    //Operators
    Dx11VertexBuffer& operator=( const Dx11VertexBuffer& Other ) = default;
    Dx11VertexBuffer& operator=( Dx11VertexBuffer&& Other ) noexcept = default;

    // Create buffer
    void CreateBuffer( const std::vector< Vertex >& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Release
    virtual void Release() override;

    // Render
    bool Render() const;
};
