#pragma once


#include "Dx11Resource.h"
#include "IDxRenderElement.h"
#include "../DxCoreInc.h"
#include "../DxMacros.h"


//=====================================================================================================================
// @brief	Dx11Buffer
//=====================================================================================================================
class Dx11Buffer : public Dx11Resource, public IDxRenderElement
{
    CLASS_DEFAULT_BODY( Dx11Buffer ) 

protected:
    ComPtr< ID3D11Buffer > BufferComPtr;
    D3D11_BUFFER_DESC      BufferDesc{};

public:
    // Construct
    Dx11Buffer();

    // Release
    virtual void Release() override;

    // Create
    void Create( const D3D11_SUBRESOURCE_DATA* SubresourceData = nullptr );

    // On render
    virtual void OnRender() const override { SetRenderState( 0 ); }

    // Set render state
    virtual bool SetRenderState( int InRegisterIndex ) const override;

    // Getters
    ID3D11Buffer*        GetBuffer() const { return BufferComPtr.Get(); }
    ID3D11Buffer* const* GetBufferAdressOf() const { return BufferComPtr.GetAddressOf(); }
    
};
