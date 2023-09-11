#include "CrLevel.h"
#include "../Asset/CrAssetManager.h"
#include "../Asset/CrMesh.h"

//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrLevel::CrLevel()
{
    CrMesh* mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "PointLight" );
    mesh->LoadTexture( "WoodenSphereDiffuse" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::Diffuse );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test2" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "PointLight" );
    mesh->LoadTexture( "BlockDiffuse" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::Diffuse );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test3" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "Specular" );
    mesh->LoadTexture( "WoodenSphereDiffuse" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::Diffuse );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test4" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "DefaultDiffuse" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "Toon" );
    mesh->LoadTexture( "BlockDiffuse" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::Diffuse );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test5" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "NormalMap" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "NormalMap" );
    mesh->LoadTexture( "BlockDiffuse" );
    mesh->LoadTexture( "BlockNormal" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::NormalMap );

    Meshes.push_back( mesh );

    mesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "Test6" );
    if ( !mesh ) return;

    mesh->LoadVertexShader( "NormalMap" );
    mesh->LoadPrimitive( "WoodenSphere_Primitive0" );
    mesh->LoadPixelShader( "NormalMap" );
    mesh->LoadTexture( "StoneDiffuse" );
    mesh->LoadTexture( "StoneNormal" );
    mesh->SetVertexStructureType( EVertexBufferStructureType::NormalMap );

    Meshes.push_back( mesh );

    TestRT = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, "TestRT" );
    if ( !TestRT ) return;
    
    TestRT->LoadPrimitive( "Plane" );
    TestRT->LoadVertexShader( "DefaultDiffuse" );
    TestRT->LoadPixelShader ( "DefaultDiffuse" );
    TestRT->SetVertexStructureType( EVertexBufferStructureType::Diffuse );
}
