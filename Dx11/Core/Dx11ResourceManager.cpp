#include "Dx11ResourceManager.h"
#include "Dx11IndexBuffer.h"
#include "Dx11PixelShader.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"
#include "../Asset/CrAssetManager.h"


static Dx11ResourceManager G_Dx11ResourceManager;
Dx11ResourceManager* GetDx11ResourceManager() { return &G_Dx11ResourceManager; }


//=====================================================================================================================
// @brief	Create vertex buffer
//=====================================================================================================================
Dx11VertexBuffer* Dx11ResourceManager::CreateVertexBuffer( const std::string& AssetName )
{
    return CreateVertexBuffer( GetAssetManager()->GetVertexBuffer( AssetName ) );    
}

//=====================================================================================================================
// @brief	Create vertex buffer
//=====================================================================================================================
Dx11VertexBuffer* Dx11ResourceManager::CreateVertexBuffer( const CrVertexBuffer* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11VertexBuffer* dxVB = _create< Dx11VertexBuffer >( AssetPtr->GetName(), VertexBuffers );
    if ( !dxVB ) return nullptr;

    dxVB->CreateBuffer( AssetPtr->GetVertices(), AssetPtr->GetUsage(), AssetPtr->GetCpuAccessFlag() );

    VertexBuffers[ AssetPtr->GetName() ] = dxVB;

    return dxVB;
}

//=====================================================================================================================
// @brief	Create index buffer
//=====================================================================================================================
Dx11IndexBuffer* Dx11ResourceManager::CreateIndexBuffer( const std::string& AssetName )
{
    return CreateIndexBuffer( GetAssetManager()->GetIndexBuffer( AssetName ) );   
}

//=====================================================================================================================
// @brief	Create index buffer
//=====================================================================================================================
Dx11IndexBuffer* Dx11ResourceManager::CreateIndexBuffer( const CrIndexBuffer* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11IndexBuffer* dxIB = _create< Dx11IndexBuffer >( AssetPtr->GetName(), IndexBuffers );
    if ( !dxIB ) return nullptr;

    dxIB->CreateBuffer( AssetPtr->GetIndices(), AssetPtr->GetUsage(), AssetPtr->GetCpuAccessFlag() );

    IndexBuffers[ AssetPtr->GetName() ] = dxIB;

    return dxIB;
}

//=====================================================================================================================
// @brief	Create vertex shader
//=====================================================================================================================
Dx11VertexShader* Dx11ResourceManager::CreateVertexShader( const std::string& AssetName )
{
    return CreateVertexShader( GetAssetManager()->GetVertexShader( AssetName ) );
}

//=====================================================================================================================
// @brief	Create vertex shader
//=====================================================================================================================
Dx11VertexShader* Dx11ResourceManager::CreateVertexShader( const CrVertexShader* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11VertexShader* dxVS = _create< Dx11VertexShader >( AssetPtr->GetName(), VertexShaders );
    if ( !dxVS ) return nullptr;

    dxVS->CreateShader( AssetPtr->GetFileName(), AssetPtr->GetEntryPoint(), AssetPtr->GetShaderModel() );
    dxVS->CreateInputLayout( AssetPtr->GetInputElements() );

    VertexShaders[ AssetPtr->GetName() ] = dxVS;

    return dxVS;
}

//=====================================================================================================================
// @brief	Create pixel shader
//=====================================================================================================================
Dx11PixelShader* Dx11ResourceManager::CreatePixelShader( const std::string& AssetName )
{
    return CreatePixelShader( GetAssetManager()->GetPixelShader( AssetName ) );
}

//=====================================================================================================================
// @brief	Create pixel shader
//=====================================================================================================================
Dx11PixelShader* Dx11ResourceManager::CreatePixelShader( const CrPixelShader* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11PixelShader* dxPS = _create< Dx11PixelShader >( AssetPtr->GetName(), PixelShaders );
    if ( !dxPS ) return nullptr;

    dxPS->CreateShader( AssetPtr->GetFileName(), AssetPtr->GetEntryPoint(), AssetPtr->GetShaderModel() );

    PixelShaders[ AssetPtr->GetName() ] = dxPS;

    return dxPS;
}

//=====================================================================================================================
// @brief	Create texture
//=====================================================================================================================
Dx11Texture2D* Dx11ResourceManager::CreateTexture2D( const std::string& AssetName )
{
    return CreateTexture2D( GetAssetManager()->GetTexture2D( AssetName ) );
}

//=====================================================================================================================
// @brief	Create texture
//=====================================================================================================================
Dx11Texture2D* Dx11ResourceManager::CreateTexture2D( const CrTexture2D* AssetPtr )
{
    if ( !AssetPtr ) return nullptr;

    Dx11Texture2D* dxTex = _create< Dx11Texture2D >( AssetPtr->GetName(), Texture2Ds );
    if ( !dxTex ) return nullptr;

    dxTex->CreateTexture( AssetPtr->GetPath(), AssetPtr->GetFormat(), AssetPtr->GetWidth(), AssetPtr->GetHeight(), AssetPtr->GetSamplingCount() );

    Texture2Ds[ AssetPtr->GetName() ] = dxTex;

    return dxTex;
}
