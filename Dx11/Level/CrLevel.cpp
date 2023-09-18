#include "CrLevel.h"
#include "../Asset/CrAssetManager.h"
#include "../Asset/CrMesh.h"
#include "../Externals/RapidJSON/include/rapidjson/document.h"
#include <fstream>

//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrLevel::CrLevel()
{
    LoadFromJson( "../Asset/Level/DevTest.json" );
}

//=====================================================================================================================
// @brief	Load from json
//=====================================================================================================================
void CrLevel::LoadFromJson( const std::string& Path )
{
    std::ifstream file( Path );
    if ( !file.is_open() ) return;

    std::string json( std::istreambuf_iterator< char >( file ), ( std::istreambuf_iterator< char >() ) );

    rapidjson::Document document;
    document.Parse( json.c_str() );

    const rapidjson::Value& meshes = document[ "Meshes" ];
    for ( rapidjson::SizeType i = 0; i < meshes.Size(); ++i )
    {
        const rapidjson::Value& mesh = meshes[ i ];

        CrMesh* crMesh = GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, mesh[ "Name" ].GetString() );
        if ( !crMesh ) continue;

        crMesh->LoadVertexShader( mesh[ "VertexShader" ].GetString() );
        crMesh->LoadPixelShader ( mesh[ "PixelShader"  ].GetString() );
        crMesh->LoadPrimitive   ( mesh[ "Primitive"    ].GetString() );
        
        crMesh->SetVertexStructureType( (EVertexBufferStructureType)mesh[ "VertexStructureType" ].GetInt() );

        const rapidjson::Value& textures = mesh[ "Textures" ];
        for ( rapidjson::SizeType t = 0; t < textures.Size(); ++t )
        {
            crMesh->LoadTexture( textures[ t ].GetString() );
        }

        const rapidjson::Value& transform = mesh[ "Transform" ];

        crMesh->GetTransform().SetLocation( transform[ "Location" ][ 0 ].GetFloat(), transform[ "Location" ][ 1 ].GetFloat(), transform[ "Location" ][ 2 ].GetFloat() );
        crMesh->GetTransform().SetRotation( transform[ "Rotation" ][ 0 ].GetFloat(), transform[ "Rotation" ][ 1 ].GetFloat(), transform[ "Rotation" ][ 2 ].GetFloat() );
        crMesh->GetTransform().SetScale   ( transform[ "Scale"    ][ 0 ].GetFloat(), transform[ "Scale"    ][ 1 ].GetFloat(), transform[ "Scale"    ][ 2 ].GetFloat() );

        crMesh->SetRenderTarget( mesh[ "RenderTarget" ].GetString() );
        crMesh->SetOpacity( mesh[ "Opacity" ].GetFloat() );

        Meshes.push_back( crMesh );
    }
}
