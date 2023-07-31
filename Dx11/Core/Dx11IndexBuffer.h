#pragma once

#include "Dx11Buffer.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11IndexBuffer
//=====================================================================================================================
class Dx11IndexBuffer : public Dx11Buffer
{
private:
    D3D11_SUBRESOURCE_DATA BufferSD;
    unsigned int           Count;

public:
    // Construct
    Dx11IndexBuffer();
    Dx11IndexBuffer( const Dx11IndexBuffer& Other ) = default;
    Dx11IndexBuffer( Dx11IndexBuffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11IndexBuffer() override = default;

    // Getters
    unsigned int GetCount() const { return Count; }

    // Operators
    Dx11IndexBuffer& operator=( const Dx11IndexBuffer& Other ) = default;
    Dx11IndexBuffer& operator=( Dx11IndexBuffer&& Other ) noexcept = default;

    // Create buffer
    void CreateBuffer( const std::vector< unsigned int >& Indices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Render
    bool Render() const;
};
