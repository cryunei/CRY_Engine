//=================================================================================================
// @file	Dx11Material.h
//
// @brief	
//
// @date	2023-4-25
//=================================================================================================


#pragma once


#include "../../Externals/DirectXTK/Inc/WICTextureLoader.h"
#include "../Core/Dx11PixelShader.h"
#include "../Core/Dx11Texture2D.h"
#include <string>


#pragma comment ( lib, "d3d11.lib" )


using namespace DirectX;


class Dx11Material
{
private:
    Dx11PixelShader* PixelShader;
    Dx11Texture2D*   Texture2D;
    
public:
    // Construct
    Dx11Material();
    
    // Initialize
    void Initialize( Dx11PixelShader* InPixelShader, Dx11Texture2D* InTexture2D );

    // Render
    void Render() const;
};
