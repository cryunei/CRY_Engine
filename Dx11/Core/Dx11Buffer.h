#pragma once


#include "Dx11Resource.h"
#include "../DxCoreInc.h"


//=====================================================================================================================
// @brief	Dx11Buffer
//=====================================================================================================================
class Dx11Buffer : public Dx11Resource
{
    CLASS_DEFAULT_BODY( Dx11Buffer ) 

protected:
    ComPtr< ID3D11Buffer > BufferComPtr;
    D3D11_BUFFER_DESC      BufferDesc{};

public:
    // Construct
    Dx11Buffer();

    // Create
    void Create( const D3D11_SUBRESOURCE_DATA* SubresourceData = nullptr );

    // Release
    virtual void Release() override;

    // Getters
    ID3D11Buffer*        GetBuffer() const { return BufferComPtr.Get(); }
    ID3D11Buffer* const* GetBufferAdressOf() const { return BufferComPtr.GetAddressOf(); }
    
};
