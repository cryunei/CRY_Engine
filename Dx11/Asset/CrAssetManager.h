#pragma once


#include "CrIndexBuffer.h"
#include "CrMesh.h"
#include "CrPrimitive.h"
#include "CrVertexShader.h"
#include "CrPixelShader.h"
#include "CrTexture2D.h"
#include <map>
#include <string>


//=====================================================================================================================
// @brief	CrAssetManager
//=====================================================================================================================
class CrAssetManager
{
private:
    std::map< std::string, CrPrimitive* >    Primitives;
    std::map< std::string, CrVertexShader* > VertexShaders;
    std::map< std::string, CrPixelShader*  > PixelShaders;
    std::map< std::string, CrTexture2D*    > Texture2Ds;
    std::map< std::string, CrMesh*         > Meshes;

public:
    // Contructor
    CrAssetManager() = default;

    // Destructor
    ~CrAssetManager() = default;

    // Create primitive
    CrPrimitive* CreatePrimitive( const std::string& Name ) { return _createAsset< CrPrimitive >( Name, Primitives );}

    // Get primitive
    CrPrimitive* GetPrimitive( const std::string& Name ) { return _getAsset< CrPrimitive >( Name, Primitives ); }

    // Create vertex shader
    CrVertexShader* CreateVertexShader( const std::string& Name ) { return _createAsset< CrVertexShader >( Name, VertexShaders ); }

    // Get vertex shader
    CrVertexShader* GetVertexShader( const std::string& Name ) { return _getAsset< CrVertexShader >( Name, VertexShaders ); }

    // Create pixel shader
    CrPixelShader* CreatePixelShader( const std::string& Name ) { return _createAsset< CrPixelShader >( Name, PixelShaders ); }

    // Get pixel shader
    CrPixelShader* GetPixelShader( const std::string& Name ) { return _getAsset< CrPixelShader >( Name, PixelShaders ); }

    // Create texture
    CrTexture2D* CreateTexture2D( const std::string& Name ) { return _createAsset< CrTexture2D >( Name, Texture2Ds ); }

    // Get texture
    CrTexture2D* GetTexture2D( const std::string& Name ) { return _getAsset< CrTexture2D >( Name, Texture2Ds ); }

    // Create mesh
    CrMesh* CreateMesh( const std::string& Name ) { return _createAsset< CrMesh >( Name, Meshes ); }

    // Get mesh
    CrMesh* GetMesh( const std::string& Name ) { return _getAsset< CrMesh >( Name, Meshes ); }

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
    AssetMap[ Name ]->SetName( Name );

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
