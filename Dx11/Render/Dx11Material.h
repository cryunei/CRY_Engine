//=================================================================================================
// @file	Dx11Material.h
//
// @brief	
//
// @date	2023-4-25
//=================================================================================================


#pragma once


#include <d3d11.h>
#include "../../Externals/DirectXTK/Inc/WICTextureLoader.h"


#pragma comment ( lib, "d3d11.lib" )


using namespace DirectX;


class Dx11Material
{
private:
    ID3D11PixelShader*        PixelShader;
    ID3D11Texture2D*          Texture2D;
    ID3D11Resource*           TextureResource;
    ID3D11ShaderResourceView* TextureSRV;
    
public:
    // Construct
    Dx11Material();
    
    // Initialize
    void Initialize( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

private:
    // Create pixel shader
    void _CreatePixelShader( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Create texture
    void _CreateTexture( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );
};
