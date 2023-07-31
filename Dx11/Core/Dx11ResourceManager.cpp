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
    CrVertexBuffer* crVB = GetAssetManager()->GetVertexBuffer( AssetName );
    if ( !crVB ) return nullptr;

    Dx11VertexBuffer* dxVB = _create< Dx11VertexBuffer >( AssetName, VertexBuffers );
    if ( !dxVB ) return nullptr;

    dxVB->CreateBuffer( crVB->GetVertices(), crVB->GetUsage(), crVB->GetCpuAccessFlag() );

    VertexBuffers[ AssetName ] = dxVB;

    return dxVB;
}

//=====================================================================================================================
// @brief	Create index buffer
//=====================================================================================================================
Dx11IndexBuffer* Dx11ResourceManager::CreateIndexBuffer( const std::string& AssetName )
{
    CrIndexBuffer* crIB = GetAssetManager()->GetIndexBuffer( AssetName );
    if ( !crIB ) return nullptr;

    Dx11IndexBuffer* dxIB = _create< Dx11IndexBuffer >( AssetName, IndexBuffers );
    if ( !dxIB ) return nullptr;

    dxIB->CreateBuffer( crIB->GetIndices(), crIB->GetUsage(), crIB->GetCpuAccessFlag() );

    IndexBuffers[ AssetName ] = dxIB;

    return dxIB;
}

//=====================================================================================================================
// @brief	Create vertex shader
//=====================================================================================================================
Dx11VertexShader* Dx11ResourceManager::CreateVertexShader( const std::string& AssetName )
{
    CrVertexShader* crVS = GetAssetManager()->GetVertexShader( AssetName );
    if ( !crVS ) return nullptr;

    Dx11VertexShader* dxVS = _create< Dx11VertexShader >( AssetName, VertexShaders );
    if ( !dxVS ) return nullptr;

    dxVS->CreateShader( crVS->GetFileName(), crVS->GetEntryPoint(), crVS->GetShaderModel() );
    dxVS->CreateInputLayout( crVS->GetInputElements() );

    VertexShaders[ AssetName ] = dxVS;

    return dxVS;
}

//=====================================================================================================================
// @brief	Create pixel shader
//=====================================================================================================================
Dx11PixelShader* Dx11ResourceManager::CreatePixelShader( const std::string& AssetName )
{
    CrPixelShader* crPS = GetAssetManager()->GetPixelShader( AssetName );
    if ( !crPS ) return nullptr;

    Dx11PixelShader* dxPS = _create< Dx11PixelShader >( AssetName, PixelShaders );
    if ( !dxPS ) return nullptr;

    dxPS->CreateShader( crPS->GetFileName(), crPS->GetEntryPoint(), crPS->GetShaderModel() );

    PixelShaders[ AssetName ] = dxPS;

    return dxPS;
}

//=====================================================================================================================
// @brief	Create texture
//=====================================================================================================================
Dx11Texture2D* Dx11ResourceManager::CreateTexture2D( const std::string& AssetName )
{
    CrTexture2D* crTex = GetAssetManager()->GetTexture2D( AssetName );
    if ( !crTex ) return nullptr;

    Dx11Texture2D* dxTex = _create< Dx11Texture2D >( AssetName, Texture2Ds );
    if ( !dxTex ) return nullptr;

    dxTex->CreateTexture( crTex->GetPath(), crTex->GetFormat(), crTex->GetWidth(), crTex->GetHeight(), crTex->GetSamplingCount() );

    Texture2Ds[ AssetName ] = dxTex;

    return dxTex;
}
