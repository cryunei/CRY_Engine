#pragma once


#include "Dx11Resource.h"
#include "../DxCoreInc.h"


class Dx11Buffer : Dx11Resource
{
protected:
    ComPtr< ID3D11Buffer > BufferComPtr;
    D3D11_BUFFER_DESC      BufferDesc{};

public:
    // Construct
    Dx11Buffer();
    Dx11Buffer( const Dx11Buffer& Other ) = default;
    Dx11Buffer( Dx11Buffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11Buffer() override = default;

    // Operators
    Dx11Buffer& operator=( const Dx11Buffer& Other ) = default;
    Dx11Buffer& operator=( Dx11Buffer&& Other ) noexcept = default;

    // Create
    void Create( const D3D11_SUBRESOURCE_DATA* SubresourceData = nullptr );

    // Release
    virtual void Release() override;

    // Getters
    ID3D11Buffer*        GetBuffer() const { return BufferComPtr.Get(); }
    ID3D11Buffer* const* GetBufferAdressOf() const { return BufferComPtr.GetAddressOf(); }
    
};
