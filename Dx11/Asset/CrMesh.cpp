#include "CrMesh.h"
#include "CrAssetManager.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrMesh::CrMesh()
: VertexShaderPtr ( nullptr )
, PrimitivePtr    ( nullptr )
, IndexBufferPtr  ( nullptr )
, PixelShaderPtr  ( nullptr )
{
}

//=====================================================================================================================
// @brief	Load vertex shader
//=====================================================================================================================
void CrMesh::LoadVertexShader( const std::string& Name )
{
    VertexShaderPtr = GetAssetManager()->CreateVertexShader( Name );
}

//=====================================================================================================================
// @brief	Load primitive
//=====================================================================================================================
void CrMesh::LoadPrimitive( const std::string& Name )
{
    PrimitivePtr = GetAssetManager()->CreatePrimitive( Name );
}

//=====================================================================================================================
// @brief	Load pixel shader
//=====================================================================================================================
void CrMesh::LoadPixelShader( const std::string& Name )
{
    PixelShaderPtr = GetAssetManager()->CreatePixelShader( Name );
}

//=====================================================================================================================
// @brief	Load texture
//=====================================================================================================================
void CrMesh::LoadTexture( const std::string& Name )
{
    Texture2DPtrs.push_back( GetAssetManager()->CreateTexture2D( Name ) );
}
