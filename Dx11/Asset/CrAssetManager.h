﻿#pragma once


#include "CrIndexBuffer.h"
#include "CrVertexBuffer.h"
#include "CrVertexShader.h"
#include "CrIndexBuffer.h"
#include <map>
#include <string>


//=====================================================================================================================
// @brief	CrAssetManager
//=====================================================================================================================
class CrAssetManager
{
private:
    std::map< std::string, CrVertexBuffer* > VertexBuffers;
    std::map< std::string, CrIndexBuffer*  > IndexBuffers;
    std::map< std::string, CrVertexShader* > VertexShaders;

public:
    // Contructor
    CrAssetManager() = default;

    // Destructor
    ~CrAssetManager() = default;

    // Create vertex buffer
    CrVertexBuffer* CreateVertexBuffer( const std::string& Name ) { return _createAsset< CrVertexBuffer >( Name, VertexBuffers );}

    // Get vertex buffer
    CrVertexBuffer* GetVertexBuffer( const std::string& Name ) { return _getAsset< CrVertexBuffer >( Name, VertexBuffers ); }

    // Create index buffer
    CrIndexBuffer* CreateIndexBuffer( const std::string& Name ) { return _createAsset< CrIndexBuffer >( Name, IndexBuffers ); }

    // Get index buffer
    CrIndexBuffer* GetIndexBuffer( const std::string& Name ) { return _getAsset< CrIndexBuffer >( Name, IndexBuffers ); }

    // Create vertex shader
    CrVertexShader* CreateVertexShader( const std::string& Name ) { return _createAsset< CrVertexShader >( Name, VertexShaders ); }

    // Get vertex shader
    CrVertexShader* GetVertexShader( const std::string& Name ) { return _getAsset< CrVertexShader >( Name, VertexShaders ); }

private:
    // Create asset
    template< typename T >
    T* _createAsset( const std::string& Name, std::map< std::string, T* >& AssetMap );

    // Get asset
    template< typename T >
    T* _getAsset( const std::string& Name, std::map< std::string, T* >& AssetMap ) const;
};


//=====================================================================================================================
// @brief	Create asset
//=====================================================================================================================
template < typename T >
T* CrAssetManager::_createAsset( const std::string& Name, std::map< std::string, T* >& AssetMap )
{
    if ( T* asset = _getAsset( Name, AssetMap ) ) return asset;

    AssetMap[ Name ] = new T();

    return AssetMap[ Name ];
}

//=====================================================================================================================
// @brief	Get asset
//=====================================================================================================================
template < typename T >
T* CrAssetManager::_getAsset( const std::string& Name, std::map< std::string, T* >& AssetMap ) const
{
    auto itrFind = AssetMap.find( Name );

    if ( itrFind != AssetMap.end() )
    {
        return itrFind->second;
    }

    return nullptr;
}

//=====================================================================================================================
// @brief	GetAssetManager
//=====================================================================================================================
CrAssetManager* GetAssetManager();
