#include "CrMesh.h"
#include "CrAssetManager.h"

//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrMesh::CrMesh()
: VertexShaderPtr ( nullptr )
, VertexBufferPtr ( nullptr )
, IndexBufferPtr  ( nullptr )
, PixelShaderPtr  ( nullptr )
, Texture2DPtr      ( nullptr )
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
// @brief	Load vertex buffer
//=====================================================================================================================
void CrMesh::LoadVertexBuffer( const std::string& Name )
{
    VertexBufferPtr = GetAssetManager()->CreateVertexBuffer( Name );
}

//=====================================================================================================================
// @brief	Load index buffer
//=====================================================================================================================
void CrMesh::LoadIndexBuffer( const std::string& Name )
{
    IndexBufferPtr = GetAssetManager()->CreateIndexBuffer( Name );
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
    Texture2DPtr = GetAssetManager()->CreateTexture2D( Name );
}
