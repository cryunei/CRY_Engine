#include "Dx11DepthStencilBuffer.h"
#include "Dx11Device.h"


//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11DepthStencilBuffer::Release()
{
    SAFE_RELEASE_COMPTR( DepthStencilBufferComPtr );
    SAFE_RELEASE_COMPTR( DepthStencilViewComPtr );
    SAFE_RELEASE_COMPTR( DepthStencilStateComPtr );
}

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11DepthStencilBuffer::Create( int Width, int Height )
{
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory( &td, sizeof( D3D11_TEXTURE2D_DESC ) );

    td.Width = Width;
    td.Height = Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;

    GetDx11Device()->CreateTexture2D( &td, nullptr, DepthStencilBufferComPtr.GetAddressOf() );

    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory( &dsd, sizeof( D3D11_DEPTH_STENCIL_DESC ) );

    dsd.DepthEnable = true;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_LESS;
    
    GetDx11Device()->CreateDepthStencilState( &dsd, DepthStencilStateComPtr.GetAddressOf() );

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    ZeroMemory( &dsvd, sizeof( D3D11_DEPTH_STENCIL_VIEW_DESC ) );

    dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvd.Texture2D.MipSlice = 0;

    GetDx11Device()->CreateDepthStencilView( DepthStencilBufferComPtr.Get(), &dsvd, DepthStencilViewComPtr.GetAddressOf() );
}

//=====================================================================================================================
// @brief	Pre render
//=====================================================================================================================
void Dx11DepthStencilBuffer::PreRender() const
{
    GetDx11DeviceContext()->ClearDepthStencilView( DepthStencilViewComPtr.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0.f );
    GetDx11DeviceContext()->OMSetDepthStencilState( DepthStencilStateComPtr.Get(), 0 );
}
