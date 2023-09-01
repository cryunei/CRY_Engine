#pragma once

#include "Dx11Texture2D.h"
#include "../Asset/CrAssetManager.h"
#include "Dx11VertexBuffer.h"
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
class Dx11VertexBuffer;
class Dx11VertexShader;


//=====================================================================================================================
// @brief	Dx11ResourceManager
//=====================================================================================================================
class Dx11ResourceManager
{
private:
    std::map< std::string, Dx11VertexBuffer* > VertexBuffers;
    std::map< std::string, Dx11IndexBuffer* >  IndexBuffers;
    std::map< std::string, Dx11VertexShader* > VertexShaders;
    std::map< std::string, Dx11PixelShader* >  PixelShaders;
    std::map< std::string, Dx11Texture2D* >    Texture2Ds;
    std::vector< Dx11ResourceRenderer* >       ResourceRenderers;

public:
    // Construct
    Dx11ResourceManager() = default;
    Dx11ResourceManager( const Dx11ResourceManager& Other ) = delete;
    Dx11ResourceManager( Dx11ResourceManager&& Other ) noexcept = delete;

    // Destruct
    ~Dx11ResourceManager() = default;

    // Operators
    Dx11ResourceManager& operator=( const Dx11ResourceManager& Other ) = delete;
    Dx11ResourceManager& operator=( Dx11ResourceManager&& Other ) noexcept = delete;

    // Create vertex buffer
    template < typename T >
    Dx11VertexBuffer* CreateVertexBuffer( const std::string& AssetName );
    template < typename T >
    Dx11VertexBuffer* CreateVertexBuffer( const CrPrimitive* AssetPtr );

    // Create index buffer
    Dx11IndexBuffer* CreateIndexBuffer( const std::string& AssetName );
    Dx11IndexBuffer* CreateIndexBuffer( const CrPrimitive* AssetPtr );

    // Create vertex shader
    Dx11VertexShader* CreateVertexShader( const std::string& AssetName );
    Dx11VertexShader* CreateVertexShader( const CrVertexShader* AssetPtr );

    // Create pixel shader
    Dx11PixelShader* CreatePixelShader( const std::string& AssetName );
    Dx11PixelShader* CreatePixelShader( const CrPixelShader* AssetPtr );

    // Create texture
    Dx11Texture2D* CreateTexture2D( const std::string& AssetName );
    Dx11Texture2D* CreateTexture2D( const CrTexture2D* AssetPtr );

    // Create empty texture
    Dx11Texture2D* CreateEmptyTexture2D( const std::string& AssetName );

    // Create resource renderer
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const std::string& AssetName, int Idx );
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const CrTexture2D* AssetPtr, int Idx );
    Dx11ResourceRenderer* CreateResourceRenderer_Texture2D( const Dx11Texture2D* TexturePtr, int Idx );

    // Get vertex buffer
    Dx11VertexBuffer* GetVertexBuffer( const std::string& AssetName ) { return _get< Dx11VertexBuffer >( AssetName, VertexBuffers ); }

    // Get index buffer
    Dx11IndexBuffer* GetIndexBuffer( const std::string& AssetName ) { return _get< Dx11IndexBuffer >( AssetName, IndexBuffers );}

    // Get vertex shader
    Dx11VertexShader* GetVertexShader( const std::string& AssetName ) { return _get< Dx11VertexShader >( AssetName, VertexShaders ); }

    // Get pixel shader
    Dx11PixelShader* GetPixelShader( const std::string& AssetName ) { return _get< Dx11PixelShader >( AssetName, PixelShaders ); }

    // Get texture
    Dx11Texture2D* GetTexture2D( const std::string& AssetName ) { return _get< Dx11Texture2D >( AssetName, Texture2Ds ); }

    // Get resource renderer
    Dx11ResourceRenderer* GetResourceRenderer_Texture2D( const Dx11Resource* ResourcePtr, int Idx );

    // Release
    void Release();

private:
    // Create
    template < typename T >
    T* _create( const std::string& Name, std::map< std::string, T* >& Map );

    // Get
    template < typename T >
    T* _get( const std::string& Name, std::map< std::string, T* >& Map );
};


//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
template < typename T >
T* Dx11ResourceManager::_create( const std::string& Name, std::map< std::string, T* >& Map )
{
    if ( T* inst = _get( Name, Map ) )
    {
        return inst;
    }

    return new T();
}

//=====================================================================================================================
// @brief	Get
//=====================================================================================================================
template < typename T >
T* Dx11ResourceManager::_get( const std::string& Name, std::map<std::string, T*>& Map )
{
    auto itrFind = Map.find( Name );

    if ( itrFind != Map.end() )
    {
        return itrFind->second;
    }

    return nullptr;
}

//=====================================================================================================================
// @brief	Create vertex buffer
//=====================================================================================================================
template < typename T >
Dx11VertexBuffer* Dx11ResourceManager::CreateVertexBuffer( const std::string& AssetName )
{
    return CreateVertexBuffer< T >( GetAssetManager()->GetPrimitive( AssetName ) );    
}

//=====================================================================================================================
// @brief	Create vertex buffer
//=====================================================================================================================
template < typename T >
Dx11VertexBuffer* Dx11ResourceManager::CreateVertexBuffer( const CrPrimitive* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11VertexBuffer* dxVB = _create< Dx11VertexBuffer >( AssetPtr->GetName(), VertexBuffers );
    if ( !dxVB ) return nullptr;

    std::vector< T > vertices;
    AssetPtr->GetVertices( vertices );

    dxVB->CreateBuffer< T >( vertices, AssetPtr->GetDx11Usage(), AssetPtr->GetDx11CpuAccessFlag() );

    VertexBuffers[ AssetPtr->GetName() ] = dxVB;

    return dxVB;
}


//=====================================================================================================================
// @brief	GetDx11ResourceManager
//=====================================================================================================================
Dx11ResourceManager* GetDx11ResourceManager();
