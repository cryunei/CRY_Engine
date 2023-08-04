#include "Dx11Material.h"
#include "../Core/Dx11PixelShader.h"
#include "../Core/Dx11Texture2D.h"
#include "../Core/Dx11VertexShader.h"


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11Material::Dx11Material()
: VertexShader( nullptr )
, PixelShader ( nullptr )
, Texture2D   ( nullptr )
{
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11Material::Initialize(  Dx11VertexShader* InVertexShader, Dx11PixelShader* InPixelShader, Dx11Texture2D* InTexture2D )
{
    VertexShader = InVertexShader;
    PixelShader = InPixelShader;
    Texture2D   = InTexture2D;
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void Dx11Material::Render() const
{
}
