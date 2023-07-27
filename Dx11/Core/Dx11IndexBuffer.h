#pragma once


#include "Dx11Resource.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11IndexBuffer
//=====================================================================================================================
class Dx11IndexBuffer : public Dx11Resource
{
private:
    ID3D11Buffer*          IndexBuffer;
    D3D11_BUFFER_DESC      IndexBufferDesc;
    D3D11_SUBRESOURCE_DATA IndexBufferSD;
    unsigned int           IndexCount;

public:
    // Construct
    Dx11IndexBuffer();
    Dx11IndexBuffer( const Dx11IndexBuffer& Other ) = default;
    Dx11IndexBuffer( Dx11IndexBuffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11IndexBuffer() = default;

    // Getters
    unsigned int GetCount() const { return IndexCount; }

    // Operators
    Dx11IndexBuffer& operator=( const Dx11IndexBuffer& Other ) = default;
    Dx11IndexBuffer& operator=( Dx11IndexBuffer&& Other ) noexcept = default;

    // Create buffer
    void CreateBuffer( const std::vector< unsigned int >& Indices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Release
    virtual void Release() override;

    // Render
    bool Render() const;
};
