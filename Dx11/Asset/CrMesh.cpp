#include "CrMesh.h"
#include "CrAssetManager.h"
#include "CrPixelShader.h"
#include "CrPrimitive.h"
#include "CrTexture2D.h"
#include "CrVertexShader.h"

//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrMesh::CrMesh()
: VertexShaderPtr    ( nullptr )
, PrimitivePtr       ( nullptr )
, IndexBufferPtr     ( nullptr )
, PixelShaderPtr     ( nullptr )
, VertexStructureType( EVertexBufferStructureType::None )
{
}

//=====================================================================================================================
// @brief	Load vertex shader
//=====================================================================================================================
void CrMesh::LoadVertexShader( const std::string& Name )
{
    VertexShaderPtr = GetAssetManager()->Get< CrVertexShader >( ECrAssetType::VertexShader, Name );
}

//=====================================================================================================================
// @brief	Load primitive
//=====================================================================================================================
void CrMesh::LoadPrimitive( const std::string& Name )
{
    PrimitivePtr = GetAssetManager()->Get< CrPrimitive >( ECrAssetType::Primitive, Name );
}

//=====================================================================================================================
// @brief	Load pixel shader
//=====================================================================================================================
void CrMesh::LoadPixelShader( const std::string& Name )
{
    PixelShaderPtr = GetAssetManager()->Get< CrPixelShader >( ECrAssetType::PixelShader, Name );
}

//=====================================================================================================================
// @brief	Load texture
//=====================================================================================================================
void CrMesh::LoadTexture( const std::string& Name )
{
    Texture2DPtrs.push_back( GetAssetManager()->Get< CrTexture2D >( ECrAssetType::Texture2D, Name ) );
}
