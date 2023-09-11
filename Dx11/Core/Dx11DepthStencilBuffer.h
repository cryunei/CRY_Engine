#pragma once


#include "Dx11Resource.h"
#include "IDxRenderElement.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11DepthStencilBuffer
//=====================================================================================================================
class Dx11DepthStencilBuffer : public Dx11Resource, public IDxRenderElement
{
    CLASS_DEFAULT_BODY( Dx11DepthStencilBuffer )

public:
    ComPtr< ID3D11Texture2D         > DepthStencilBufferComPtr;
    ComPtr< ID3D11DepthStencilView  > DepthStencilViewComPtr;
    ComPtr< ID3D11DepthStencilState > DepthStencilStateComPtr;

public:
    // Construct
    Dx11DepthStencilBuffer() = default;

    // Release
    virtual void Release() override;

    // Create
    void Create( int Width, int Height );

    // Pre render 
    virtual void PreRender() const override;

    // Getter
    ID3D11DepthStencilView* GetView() const { return DepthStencilViewComPtr.Get(); }
    ID3D11Texture2D* GetBuffer() const { return DepthStencilBufferComPtr.Get(); }
};
