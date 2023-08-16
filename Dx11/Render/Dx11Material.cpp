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
void Dx11Material::InitializeTexture2Ds( const std::vector< Dx11Texture2D* >& InTexture2D )
{
    int idx = 0;
    for ( const Dx11Texture2D* texture2D : InTexture2D )
    {
        Texture2Ds.emplace_back( texture2D, idx++ );
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

    return &Texture2Ds[ Idx ];
}
