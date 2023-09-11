#include "Dx11ObjectManager.h"
#include "Dx11DepthStencilBuffer.h"
#include "Dx11IndexBuffer.h"
#include "Dx11PixelShader.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexShader.h"
#include "../Asset/CrTexture2D.h"
#include "../Render/Dx11ResourceRenderer.h"
#include "../Asset/CrAssetManager.h"


static Dx11ObjectManager G_Dx11ObjectManager;
Dx11ObjectManager* GetDx11ObjectManager() { return &G_Dx11ObjectManager; }


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11ObjectManager::Dx11ObjectManager()
{
    for ( int i = 0; i < DX11_RESOURCE_TYPE_COUNT; ++i )
    {
        Resources.emplace_back();
    }

    ResourceToCrAssetTypeConv.reserve( DX11_RESOURCE_TYPE_COUNT );
    ResourceToCrAssetTypeConv.insert( ResourceToCrAssetTypeConv.end(),
    {
        ECrAssetType::Primitive,    // EDx11ResourceType::VertexBuffer
        ECrAssetType::Primitive,    // EDx11ResourceType::IndexBuffer
        ECrAssetType::Max,          // EDx11ResourceType::ConstantBuffer
        ECrAssetType::Max,          // EDx11ResourceType::DepthStencilBuffer
        ECrAssetType::VertexShader, // EDx11ResourceType::VertexBuffer
        ECrAssetType::PixelShader,  // EDx11ResourceType::PixelShader
        ECrAssetType::Texture2D     // EDx11ResourceType::Texture2D
    } );
}

//=====================================================================================================================
// @brief	Get resource
//=====================================================================================================================
Dx11Object* Dx11ObjectManager::Get( EDx11ResourceType Type, const std::string& Name )
{
    Dx11Object* object = nullptr;
    switch ( Type )
    {
    case EDx11ResourceType::VertexBuffer:       object = Get< Dx11VertexBuffer       > ( Type, Name ); break;
    case EDx11ResourceType::IndexBuffer:        object = Get< Dx11IndexBuffer        > ( Type, Name ); break;
    case EDx11ResourceType::ConstantBuffer:     object = Get< Dx11ConstantBuffer     > ( Type, Name ); break;
    case EDx11ResourceType::DepthStencilBuffer: object = Get< Dx11DepthStencilBuffer > ( Type, Name ); break;
    case EDx11ResourceType::VertexShader:       object = Get< Dx11VertexShader       > ( Type, Name ); break;
    case EDx11ResourceType::PixelShader:        object = Get< Dx11PixelShader        > ( Type, Name ); break;
    case EDx11ResourceType::Texture2D:          object = Get< Dx11Texture2D          > ( Type, Name ); break;
    }

    return object;
}

//=====================================================================================================================
// @brief	Get resource from crasset
//=====================================================================================================================
Dx11Object* Dx11ObjectManager::GetFrom( EDx11ResourceType Type, const std::string& AssetName )
{
    return GetFrom( Type, GetAssetManager()->Get( ResourceToCrAssetTypeConv[ (int)Type ], AssetName ) );
}

//=====================================================================================================================
// @brief	Get resource from crasset
//=====================================================================================================================
Dx11Object* Dx11ObjectManager::GetFrom( EDx11ResourceType Type, const CrAsset* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11Object* object = Get( Type, AssetPtr->GetName() );
    if ( !object ) return nullptr;

    object->CreateFrom( AssetPtr );

    return object;
}

//=====================================================================================================================
// @brief	Create resource renderer
//=====================================================================================================================
Dx11ResourceRenderer* Dx11ObjectManager::CreateResourceRenderer_Texture2D( const std::string& AssetName, int Idx )
{
    CrAsset* asset = GetAssetManager()->Get( ECrAssetType::Texture2D, AssetName );
    if ( !asset ) return nullptr;

    return CreateResourceRenderer_Texture2D( (CrTexture2D*)( asset ), Idx );
}

//=====================================================================================================================
// @brief	Create resource renderer
//=====================================================================================================================
Dx11ResourceRenderer* Dx11ObjectManager::CreateResourceRenderer_Texture2D( const CrTexture2D* AssetPtr, int Idx )
{
    if ( !AssetPtr ) return nullptr;

    Dx11Texture2D* dxTex = GetFrom< Dx11Texture2D >( EDx11ResourceType::Texture2D, AssetPtr );
    if ( !dxTex ) return nullptr;

    return CreateResourceRenderer_Texture2D( dxTex, Idx );
}

 //=====================================================================================================================
// @brief	Create resource renderer
//=====================================================================================================================
Dx11ResourceRenderer* Dx11ObjectManager::CreateResourceRenderer_Texture2D( const Dx11Texture2D* TexturePtr, int Idx )
{
    Dx11ResourceRenderer* dxRR = GetResourceRenderer_Texture2D( TexturePtr, Idx );
    if ( !dxRR )
    {
        dxRR = new Dx11ResourceRenderer( TexturePtr, Idx );
        ResourceRenderers.push_back( dxRR );
    }

    return dxRR;
}

//=====================================================================================================================
// @brief	Get resource renderer
//=====================================================================================================================
Dx11ResourceRenderer* Dx11ObjectManager::GetResourceRenderer_Texture2D( const Dx11Resource* ResourcePtr, int Idx )
{
    auto itr = std::find_if( ResourceRenderers.begin(), ResourceRenderers.end(), [ ResourcePtr, Idx ] ( const Dx11ResourceRenderer* dxRR )
    {
        return dxRR->GetResourcePtr() == ResourcePtr && dxRR->GetRegisterIndex() == Idx;
    } );

    if ( itr != ResourceRenderers.end() )
    {
        return *itr;
    }

    return nullptr;
}

//=====================================================================================================================
// @brief	Get map
//=====================================================================================================================
Dx11ObjectManager::TResourceMap& Dx11ObjectManager::_getMap( EDx11ResourceType Type )
{
    return Resources[ (int)( Type ) ];
}
