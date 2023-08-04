#pragma once


#include "Dx11Buffer.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11VertexBuffer
//=====================================================================================================================
class Dx11VertexBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11VertexBuffer )

private:
    unsigned int             Count;
    unsigned int             Stride;
    unsigned int             Offset;
    D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;

public:
    // Construct
    Dx11VertexBuffer() = default;

    // Create buffer
    void CreateBuffer( const std::vector< Vertex >& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set render state
    virtual bool SetRenderState() const override;

    // Getters
    unsigned int GetCount() const { return Count; }
};
