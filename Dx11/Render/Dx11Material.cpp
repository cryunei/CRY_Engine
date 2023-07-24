//=================================================================================================
// @file	Dx11Material.cpp
//
// @date	2023-4-25
//=================================================================================================


#include "Dx11Material.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"
#include <d3dcompiler.h>


//=================================================================================================
// @brief	Construct
//=================================================================================================
Dx11Material::Dx11Material()
: PixelShader     ( nullptr )
, Texture2D       ( nullptr )
, TextureResource ( nullptr )
, TextureSRV      ( nullptr )
{
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Material::Initialize()
{
    _createPixelShader();
    _createTexture();
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Material::Render() const
{
    GetDx11DeviceContext()->PSSetShaderResources( 0, 1, &TextureSRV );
    GetDx11DeviceContext()->PSSetSamplers(0, 1, &TextureSS );
}

//=================================================================================================
// @brief	Create pixel shader
//=================================================================================================
void Dx11Material::_createPixelShader()
{
    ID3D10Blob* ps = Dx11ResourceFactory::CompileShader( L"../Shader/shader.hlsl", "PS", "ps_4_0" );

    GetDx11Device()->CreatePixelShader ( ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &PixelShader  );
    GetDx11DeviceContext()->PSSetShader( PixelShader,  0, 0 );
}

//=================================================================================================
// @brief	Create texture
//=================================================================================================
void Dx11Material::_createTexture()
{
   // create texture
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory( &td, sizeof( D3D11_TEXTURE2D_DESC ) );

    td.Height = 800;
    td.Width = 480;
    td.MipLevels = 0;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    td.CPUAccessFlags = 0;
    td.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    GetDx11Device()->CreateTexture2D( &td, nullptr, &Texture2D );

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
    GetDx11Device()->CreateSamplerState( &sd, &TextureSS );

    CoInitialize( nullptr );

    CreateWICTextureFromFile( GetDx11Device(), L"../Asset/Texture/mpm_vol.08_p16_light_side_A_diff.jpg", &TextureResource, &TextureSRV );
}
