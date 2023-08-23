#include "CrLevel.h"
#include "../Asset/CrAssetManager.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrLevel::CrLevel()
{
    CrMesh* mesh = GetAssetManager()->CreateMesh( "Test" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "PointLight" );
    mesh->LoadTexture( "WoodenSphereDiffuse" );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->CreateMesh( "Test2" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "PointLight" );
    mesh->LoadTexture( "BlockDiffuse" );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->CreateMesh( "Test3" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "Specular" );
    mesh->LoadTexture( "WoodenSphereDiffuse" );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->CreateMesh( "Test4" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "Toon" );
    mesh->LoadTexture( "BlockDiffuse" );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->CreateMesh( "Test5" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "NormalMap" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "NormalMap" );
    mesh->LoadTexture( "BlockDiffuse" );
    mesh->LoadTexture( "BlockNormal" );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->CreateMesh( "Test6" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "NormalMap" );
    mesh->LoadVertexBuffer( "WoodenSphere_Vertex0" );
    mesh->LoadPixelShader( "NormalMap" );
    mesh->LoadTexture( "StoneDiffuse" );
    mesh->LoadTexture( "StoneNormal" );

    Meshes.push_back( mesh );
}
