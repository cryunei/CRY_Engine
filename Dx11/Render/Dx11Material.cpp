#include "Dx11Material.h"
#include "../Core/Dx11PixelShader.h"
#include "../Core/Dx11Texture2D.h"
#include "../Core/Dx11Resource.h"
#include "../Core/Dx11VertexShader.h"


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11Material::Dx11Material()
: VertexShader( nullptr )
, PixelShader ( nullptr )
{
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11Material::Initialize(  Dx11VertexShader* InVertexShader, Dx11PixelShader* InPixelShader )
{
    VertexShader = InVertexShader;
    PixelShader = InPixelShader;
}

//=====================================================================================================================
// @brief	Initialize texture 2d array
//=====================================================================================================================
void Dx11Material::InitializeTexture2Ds( const std::vector< Dx11ResourceRenderer* >& InResourceRenderers )
{
    Texture2Ds = InResourceRenderers;
}

//=====================================================================================================================
// @brief	Increase render count
//=====================================================================================================================
void Dx11Material::IncreaseRenderCount() const
{
    if ( VertexShader ) VertexShader->IncreaseRenderCount();
    if ( PixelShader  ) PixelShader ->IncreaseRenderCount();

    for ( auto& texture2D : Texture2Ds )
    {
        texture2D->IncreaseRenderCount();
    }
}

//=====================================================================================================================
// @brief	Decrease render count
//=====================================================================================================================
void Dx11Material::DecreaseRenderCount() const
{
    if ( VertexShader ) VertexShader->DecreaseRenderCount();
    if ( PixelShader  ) PixelShader ->DecreaseRenderCount();

    for ( auto& texture2D : Texture2Ds )
    {
        texture2D->DecreaseRenderCount();
    }
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void Dx11Material::Render() const
{
}

//=====================================================================================================================
// @brief	Get texture 2d renderer
//=====================================================================================================================
const Dx11ResourceRenderer* Dx11Material::GetRenderer_Texture2D( int Idx ) const
{
    if ( Idx < 0 || Idx >= Texture2Ds.size() ) return nullptr;

    return Texture2Ds[ Idx ];
}
