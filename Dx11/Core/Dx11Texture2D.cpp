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
void Dx11Texture2D::CreateTexture( const std::string& TexturePath, DXGI_FORMAT Format, UINT Width, UINT Height, UINT SamplingCount )
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

    GetDx11Device()->CreateTexture2D( &Desc, nullptr, Texture2DComPtr.GetAddressOf() );

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
    GetDx11Device()->CreateSamplerState( &sd, TextureSSComPtr.GetAddressOf() );

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