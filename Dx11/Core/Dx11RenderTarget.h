#pragma once

#include "Dx11DepthStencilBuffer.h"
#include "Dx11Object.h"
#include "Dx11Texture2D.h"
#include "../DxTypes.h"


class CrTexture2D;


//=====================================================================================================================
// @brief	Dx11RenderTarget
//=====================================================================================================================
class Dx11RenderTarget : public Dx11Object
{
    CLASS_DEFAULT_BODY( Dx11RenderTarget )

private:
    Dx11Texture2D* Texture2DPtr;
    Dx11DepthStencilBuffer* DepthStencilBufferPtr;
    D3D11_VIEWPORT Viewport;

    ComPtr< ID3D11RenderTargetView > RenderTargetViewComPtr;

public:
    // Construct
    Dx11RenderTarget() = default;

    // Initialize
    void Initialize( unsigned int Width, unsigned int Height );

    // Initialize
    void Initialize( const std::string& Name, unsigned int Width, unsigned int Height, DXGI_FORMAT Format );

    // Clear
    void Clear( float Color[ 4 ] ) const;

    // Set render target
    void SetRenderTarget() const;

    // Release
    virtual void Release() override;

    // Get texture
    Dx11Texture2D* GetTexture2D() const { return Texture2DPtr; }
    const D3D11_VIEWPORT& GetViewport() const { return Viewport; }

private:

    // Set viewport
    void _setViewport( unsigned int Width, unsigned int Height );
};
