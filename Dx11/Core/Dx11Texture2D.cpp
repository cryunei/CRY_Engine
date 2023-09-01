#include "Dx11Texture2D.h"
#include "Dx11Device.h"
#include "../Util/UtilString.h"
#include <DirectXTK/Inc/WICTextureLoader.h>


//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11Texture2D::Release()
{
    SAFE_RELEASE_COMPTR( TextureSSComPtr );
    SAFE_RELEASE_COMPTR( Texture2DComPtr );
    SAFE_RELEASE_COMPTR( TextureResourceComPtr );
    SAFE_RELEASE_COMPTR( TextureSRVComPtr );    
}

//=====================================================================================================================
// @brief	Create texture
//=====================================================================================================================
void Dx11Texture2D::CreateTexture( DXGI_FORMAT Format, UINT Width, UINT Height, UINT SamplingCount )
{
    // create texture    
    ZeroMemory( &Desc, sizeof( D3D11_TEXTURE2D_DESC ) );

    Desc.Height = Width;
    Desc.Width = Height;
    Desc.MipLevels = 0;
    Desc.ArraySize = 1;
    Desc.Format = Format;
    Desc.SampleDesc.Count = SamplingCount;
    Desc.SampleDesc.Quality = 0;
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    Desc.CPUAccessFlags = 0;
    Desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

     HRESULT hr = GetDx11Device()->CreateTexture2D( &Desc, nullptr, Texture2DComPtr.GetAddressOf() );
}

//=====================================================================================================================
// @brief	Create sampler
//=====================================================================================================================
void Dx11Texture2D::CreateSampler()
{
    // create sample state
    D3D11_SAMPLER_DESC sd;
    ZeroMemory( &sd, sizeof( D3D11_SAMPLER_DESC ) );

    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MipLODBias = 0.0f;
    sd.MaxAnisotropy = 1;
    sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sd.BorderColor[ 0 ] = 0;
    sd.BorderColor[ 1 ] = 0;
    sd.BorderColor[ 2 ] = 0;
    sd.BorderColor[ 3 ] = 0;
    sd.MinLOD = 0;
    sd.MaxLOD = D3D11_FLOAT32_MAX;

    // Create the texture sampler state.
    HRESULT hr = GetDx11Device()->CreateSamplerState( &sd, TextureSSComPtr.GetAddressOf() );
}

//=====================================================================================================================
// @brief	Create shader resource view
//=====================================================================================================================
void Dx11Texture2D::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
    ZeroMemory( &srvd, sizeof( D3D11_SHADER_RESOURCE_VIEW_DESC ) );

    srvd.Format = Desc.Format;
    srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvd.Texture2D.MostDetailedMip = 0;
    srvd.Texture2D.MipLevels = 1;

    HRESULT hr = GetDx11Device()->CreateShaderResourceView( Texture2DComPtr.Get(), &srvd, TextureSRVComPtr.GetAddressOf() );
}

//=====================================================================================================================
// @brief	Load from file
//=====================================================================================================================
void Dx11Texture2D::LoadFromFile( const std::string& TexturePath )
{
    CreateSampler();

    CoInitialize( nullptr );

    CreateWICTextureFromFile( GetDx11Device(), ToWstring( TexturePath ).c_str(), TextureResourceComPtr.GetAddressOf(), TextureSRVComPtr.GetAddressOf() );
}

//=====================================================================================================================
// @brief	Set render state
//=====================================================================================================================
bool Dx11Texture2D::SetRenderState( int InRegisterIndex ) const
{
    GetDx11DeviceContext()->PSSetShaderResources( InRegisterIndex, 1, TextureSRVComPtr.GetAddressOf() );
    GetDx11DeviceContext()->PSSetSamplers( 0, 1, TextureSSComPtr.GetAddressOf() );

    return true;
}