#include "CrAssetManager.h"
#include "CrAsset.h"
#include "CrMesh.h"
#include "CrPixelShader.h"
#include "CrPrimitive.h"
#include "CrTexture2D.h"
#include "CrVertexShader.h"


CrAssetManager G_AssetManager;
CrAssetManager* GetAssetManager() { return &G_AssetManager; }


//=====================================================================================================================
// @brief	Contructor
//=====================================================================================================================
CrAssetManager::CrAssetManager()
{
    Assets.reserve( CRASSET_TYPE_COUNT );
    for ( int i = 0; i < CRASSET_TYPE_COUNT; ++i )
    {
        Assets.emplace_back();
    }
}

//=====================================================================================================================
// @brief	Get
//=====================================================================================================================
CrAsset* CrAssetManager::Get( ECrAssetType Type, const std::string& Name )
{
    CrAsset* asset = nullptr;

    switch ( Type )
    {
    case ECrAssetType::Primitive:    asset = _getAsset< CrPrimitive    >( Name, _getMap( Type ) ); break;
    case ECrAssetType::VertexShader: asset = _getAsset< CrVertexShader >( Name, _getMap( Type ) ); break;
    case ECrAssetType::PixelShader:  asset = _getAsset< CrPixelShader  >( Name, _getMap( Type ) ); break;
    case ECrAssetType::Texture2D:    asset = _getAsset< CrTexture2D    >( Name, _getMap( Type ) ); break;
    case ECrAssetType::Mesh:         asset = _getAsset< CrMesh         >( Name, _getMap( Type ) ); break;
    }
    
    return asset;
}