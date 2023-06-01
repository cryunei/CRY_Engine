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
    ID3D11SamplerState*       TextureSS;
    
public:
    // Construct
    Dx11Material();
    
    // Initialize
    void Initialize();

    // Render
    void Render() const;

private:
    // Create pixel shader
    void _createPixelShader();

    // Create texture
    void _createTexture();
};
