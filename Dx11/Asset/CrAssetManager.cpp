#include "CrAssetManager.h"
#include "CrAsset.h"
#include "CrMesh.h"
#include "CrPixelShader.h"
#include "CrPrimitive.h"
#include "CrTexture2D.h"
#include "CrVertexShader.h"
#include "../Actor/CrMeshActor.h"
#include "..\Actor\CrReflector.h"


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
    case ECrAssetType::Primitive:    asset = _getAsset< CrPrimitive    >( Type, Name ); break;
    case ECrAssetType::VertexShader: asset = _getAsset< CrVertexShader >( Type, Name ); break;
    case ECrAssetType::PixelShader:  asset = _getAsset< CrPixelShader  >( Type, Name ); break;
    case ECrAssetType::Texture2D:    asset = _getAsset< CrTexture2D    >( Type, Name ); break;
    case ECrAssetType::Mesh:         asset = _getAsset< CrMesh         >( Type, Name ); break;
    case ECrAssetType::MeshActor:    asset = _getAsset< CrMeshActor    >( Type, Name ); break;
    case ECrAssetType::Reflector:    asset = _getAsset< CrReflector    >( Type, Name ); break;
    }
    
    return asset;
}