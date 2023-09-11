#pragma once

#include "CrAssetTypes.h"
#include <map>
#include <vector>
#include <string>


class CrAsset;


//=====================================================================================================================
// @brief	CrAssetManager
//=====================================================================================================================
class CrAssetManager
{
public:
    using TAssetMap = std::map< std::string, CrAsset* >;
    using TAssetMapVector = std::vector< TAssetMap >;

private:
    TAssetMapVector Assets;

public:
    // Contructor
    CrAssetManager();

    // Destructor
    ~CrAssetManager() = default;

    // Get asset
    template< typename T >
    T* Get( ECrAssetType Type, const std::string& Name );
    CrAsset* Get( ECrAssetType Type, const std::string& Name );

private:
    // Get asset
    template< typename T >
    T* _getAsset( const std::string& Name, TAssetMap& AssetMap ) const;

    // Get map
    TAssetMap& _getMap( ECrAssetType Type ) { return Assets[ ( int )( Type ) ]; }
};


//=====================================================================================================================
// @brief	Get asset
//=====================================================================================================================
template < typename T >
T* CrAssetManager::Get( ECrAssetType Type, const std::string& Name )
{
    return (T*)( Get( Type, Name ) );
}

//=====================================================================================================================
// @brief	Get asset
//=====================================================================================================================
template < typename T >
T* CrAssetManager::_getAsset( const std::string& Name, TAssetMap& AssetMap ) const
{
    auto itrFind = AssetMap.find( Name );

    T* asset = nullptr;
    if ( itrFind == AssetMap.end() )
    {
        asset = new T();
        asset->SetName( Name );

        AssetMap.insert( std::make_pair( Name, asset ) );
    }
    else
    {
        asset = (T*)( itrFind->second );
    }

    return asset;
}

//=====================================================================================================================
// @brief	GetAssetManager
//=====================================================================================================================
CrAssetManager* GetAssetManager();
