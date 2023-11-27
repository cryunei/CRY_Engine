#include "Dx11RenderTarget.h"
#include "Dx11Device.h"
#include "Dx11ObjectManager.h"


//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11RenderTarget::Initialize( unsigned int Width, unsigned int Height )
{
    Release();

    _setViewport( Width, Height );

    Texture2DPtr = GetDx11ObjectManager()->Get< Dx11Texture2D >( EDx11ResourceType::Texture2D, "ScreenBuffer" );
    if ( !Texture2DPtr ) return;

    GetSwapChain()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )Texture2DPtr->GetTextureAddress() );
    if ( !Texture2DPtr->GetTexture() ) return;

    GetDx11Device()->CreateRenderTargetView( Texture2DPtr->GetTexture(), nullptr, RenderTargetViewComPtr.GetAddressOf() );

    DepthStencilBufferPtr = GetDx11ObjectManager()->Get< Dx11DepthStencilBuffer >( EDx11ResourceType::DepthStencilBuffer, "ScreenBuffer" );
    DepthStencilBufferPtr->Create( Width, Height );
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11RenderTarget::Initialize( const std::string& Name, unsigned int Width, unsigned int Height, DXGI_FORMAT Format )
{
    Release();

    _setViewport( Width, Height );

    Texture2DPtr = GetDx11ObjectManager()->Get< Dx11Texture2D >( EDx11ResourceType::Texture2D, Name );
    if ( !Texture2DPtr ) return;

    Texture2DPtr->CreateTexture( Format, Width, Height, 1 );
    Texture2DPtr->CreateSampler();
    
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    ZeroMemory( &rtvd, sizeof( D3D11_RENDER_TARGET_VIEW_DESC ) );

    rtvd.Format = Format;
    rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    GetDx11Device()->CreateRenderTargetView( Texture2DPtr->GetTexture(), &rtvd, RenderTargetViewComPtr.GetAddressOf() );

    Texture2DPtr->CreateSRV();

    DepthStencilBufferPtr = GetDx11ObjectManager()->Get< Dx11DepthStencilBuffer >( EDx11ResourceType::DepthStencilBuffer, Name );
    DepthStencilBufferPtr->Create( Width, Height );
}

//=====================================================================================================================
// @brief	Clear
//=====================================================================================================================
void Dx11RenderTarget::Clear( float Color[ 4 ] ) const
{
    GetDx11DeviceContext()->ClearRenderTargetView( RenderTargetViewComPtr.Get(), Color );
    DepthStencilBufferPtr->PreRender();
}

//=====================================================================================================================
// @brief	Set render target
//=====================================================================================================================
void Dx11RenderTarget::SetRenderTarget() const
{
    GetDx11DeviceContext()->RSSetViewports( 1, &Viewport );
    GetDx11DeviceContext()->OMSetRenderTargets( 1, RenderTargetViewComPtr.GetAddressOf(), DepthStencilBufferPtr->GetView() );

    DepthStencilBufferPtr->OnRender();
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11RenderTarget::Release()
{
    SAFE_RELEASE_COMPTR( RenderTargetViewComPtr );
}

//=====================================================================================================================
// @brief	Set viewport
//=====================================================================================================================
void Dx11RenderTarget::_setViewport( unsigned Width, unsigned Height )
{
    ZeroMemory( &Viewport, sizeof( D3D11_VIEWPORT ) );

    Viewport.TopLeftX = 0;
    Viewport.TopLeftY = 0;
    Viewport.MinDepth = 0.f;
    Viewport.MaxDepth = 1.f;
    Viewport.Width  = (float)( Width );
    Viewport.Height = (float)( Height );
}
