#pragma once

#include "Dx11ConstantBuffer.h"
#include "Dx11CoreTypes.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexBuffer.h"
#include "../Asset/CrAssetManager.h"
#include <map>

class Dx11Resource;
class Dx11ResourceRenderer;
class CrTexture2D;
class CrPixelShader;
class CrVertexShader;
class CrIndexBuffer;
class CrPrimitive;
class Dx11Texture2D;
class Dx11PixelShader;
class Dx11IndexBuffer;
class Dx11VertexShader;


//=====================================================================================================================
// @brief	Dx11ObjectManager
//=====================================================================================================================
class Dx11ObjectManager
{
public:
    using TResourceMap = std::map< std::string, Dx11Object* >;
    using TResourceMapVector = std::vector< TResourceMap >;

    using TResourceRendererVector = std::vector< Dx11ResourceRenderer* >;
    using TResourceTypeToCrAssetTypeConv = std::vector< ECrAssetType >; 

private:
    TResourceMapVector      Resources;
    TResourceRendererVector ResourceRenderers;

    TResourceTypeToCrAssetTypeConv ResourceToCrAssetTypeConv;

public:
    // Construct
    Dx11ObjectManager();
    Dx11ObjectManager( const Dx11ObjectManager& Other ) = delete;
    Dx11ObjectManager( Dx11ObjectManager&& Other ) noexcept = delete;

    // Destruct
    ~Dx11ObjectManager() = default;

    // Operators
    Dx11ObjectManager& operator=( const Dx11ObjectManager& Other ) = delete;
    Dx11ObjectManager& operator=( Dx11ObjectManager&& Other ) noexcept = delete;

    // Get object
    template< typename T >
    T* Get( EDx11ResourceType Type, const std::string& Name );
    Dx11Object* Get( EDx11ResourceType Type, const std::string& Name );    

    // Get object from crasset
    template< typename T >
    T* GetFrom( EDx11ResourceType Type, const std::string& AssetName );
    template< typename T >
    T* GetFrom( EDx11ResourceType Type, const CrAsset* AssetPtr );
    Dx11Object* GetFrom( EDx11ResourceType Type, const std::string& AssetName );
    Dx11Object* GetFrom( EDx11ResourceType Type, const CrAsset* AssetPtr );

    // Create resource renderer
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const std::string& AssetName, int Idx );
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const CrTexture2D* AssetPtr, int Idx );
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const Dx11Texture2D* TexturePtr, int Idx );

    // Get resource renderer
    Dx11ResourceRenderer* GetResourceRenderer_Texture2D( const Dx11Resource* ResourcePtr, int Idx );

    // Release
    void Release();

private:
    // Get
    template < typename T >
    T* _get( const std::string& Name, std::map< std::string, Dx11Object* >& Map );

    // Get map
    TResourceMap& _getMap( EDx11ResourceType Type );
};


//=====================================================================================================================
// @brief	Get object
//=====================================================================================================================
template < typename T >
T* Dx11ObjectManager::Get( EDx11ResourceType Type, const std::string& Name )
{
    return _get< T >( Name, _getMap( Type ) ); 
}

//=====================================================================================================================
// @brief	Get object from crasset
//=====================================================================================================================
template < typename T >
T* Dx11ObjectManager::GetFrom( EDx11ResourceType Type, const std::string& AssetName )
{
    return (T*)( GetFrom( Type, AssetName ) );
}

//=====================================================================================================================
// @brief	Get object from crasset
//=====================================================================================================================
template < typename T >
T* Dx11ObjectManager::GetFrom( EDx11ResourceType Type, const CrAsset* AssetPtr )
{
    return (T*)( GetFrom( Type, AssetPtr ) );
}

//=====================================================================================================================
// @brief	Get
//=====================================================================================================================
template < typename T >
T* Dx11ObjectManager::_get( const std::string& Name, std::map<std::string, Dx11Object* >& Map )
{
    auto itrFind = Map.find( Name );

    T* ret = nullptr;
    if ( itrFind == Map.end() )
    {
        ret = new T();
        Map.insert( std::make_pair( Name, ret ) );
    }
    else
    {
        ret = (T*)( itrFind->second );
    }

    return ret;
}


//=====================================================================================================================
// @brief	GetDx11ResourceManager
//=====================================================================================================================
Dx11ObjectManager* GetDx11ObjectManager();
