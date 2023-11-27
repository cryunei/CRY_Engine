#include "CrLevel.h"
#include "../Dx11.h"
#include "../Actor/CrMeshActor.h"
#include "../Actor/CrReflector.h"
#include "../Asset/CrAssetManager.h"
#include "../Asset/CrMesh.h"
#include "../Render/Dx11Renderer.h"
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

    _LoadRenderTargetsFromJson( document );
    _LoadMeshesFromJson( document );
    _LoadActorsFromJson( document );
    _LoadReflectorsFromJson( document );

    file.close();
}

//=====================================================================================================================
// @brief	Load render targets from json
//=====================================================================================================================
void CrLevel::_LoadRenderTargetsFromJson( const rapidjson::Document& Document ) const
{
    const rapidjson::Value& renderTargets = Document[ "RenderTargets" ];

    for ( rapidjson::SizeType i = 0; i < renderTargets.Size(); ++i )
    {
        const rapidjson::Value& renderTarget = renderTargets[ i ];
        const rapidjson::Value& name   = renderTarget[ "Name"       ];
        const rapidjson::Value& width  = renderTarget[ "Width"      ];
        const rapidjson::Value& height = renderTarget[ "Height"     ];
        const rapidjson::Value& color  = renderTarget[ "ClearColor" ];
        const rapidjson::Value& format = renderTarget[ "Format"     ];

        G_Dx11Renderer.AddRenderTarget( name.GetString(), width.GetInt(), height.GetInt(), DXGI_FORMAT_R8G8B8A8_UNORM );
    }
}

//=====================================================================================================================
// @brief	Load meshes from json
//=====================================================================================================================
void CrLevel::_LoadMeshesFromJson( const rapidjson::Document& Document )
{
    const rapidjson::Value& meshes = Document[ "Meshes" ];
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
    }
}

//=====================================================================================================================
// @brief	Load actors from json
//=====================================================================================================================
void CrLevel::_LoadActorsFromJson( const rapidjson::Document& Document )
{
    const rapidjson::Value& actors = Document[ "Actors" ];

    Actors.reserve( actors.Size() );

    for ( rapidjson::SizeType i = 0; i < actors.Size(); ++i )
    {
        const rapidjson::Value& actor = actors[ i ];

        CrMeshActor* crActor = nullptr;
        if ( actor[ "Type" ].GetInt() == 1 )
        {
            crActor = GetAssetManager()->Get< CrReflector >( ECrAssetType::Reflector, actor[ "Name" ].GetString() );            
        }
        else
        {
            crActor = GetAssetManager()->Get< CrMeshActor >( ECrAssetType::MeshActor, actor[ "Name" ].GetString() );
        }
        
        crActor->SetMesh( GetAssetManager()->Get< CrMesh >( ECrAssetType::Mesh, actor[ "Mesh" ].GetString() ) );

        const rapidjson::Value& transform = actor[ "Transform" ];

        crActor->GetTransform()->SetLocation( transform[ "Location" ][ 0 ].GetFloat(), transform[ "Location" ][ 1 ].GetFloat(), transform[ "Location" ][ 2 ].GetFloat() );
        crActor->GetTransform()->SetRotation( transform[ "Rotation" ][ 0 ].GetFloat(), transform[ "Rotation" ][ 1 ].GetFloat(), transform[ "Rotation" ][ 2 ].GetFloat() );
        crActor->GetTransform()->SetScale   ( transform[ "Scale"    ][ 0 ].GetFloat(), transform[ "Scale"    ][ 1 ].GetFloat(), transform[ "Scale"    ][ 2 ].GetFloat() );

        const rapidjson::Value& renderTargets = actor[ "RenderTargets" ];
        for ( rapidjson::SizeType r = 0; r < renderTargets.Size(); ++r )
        {
            crActor->AddRenderTarget( renderTargets[ r ].GetString() );
        }

        crActor->SetOpacity( actor[ "Opacity" ].GetFloat() );
        crActor->SetReflect( actor[ "Reflect" ].GetBool()  );

        Actors.push_back( crActor );
    }
}

//=====================================================================================================================
// @brief	Load reflectors from json
//=====================================================================================================================
void CrLevel::_LoadReflectorsFromJson( const rapidjson::Document& Document )
{
    const rapidjson::Value& reflectors = Document[ "Reflectors" ];

    Reflectors.reserve( reflectors.Size() );

    for ( rapidjson::SizeType i = 0; i < reflectors.Size(); ++i )
    {
        const rapidjson::Value& reflector = reflectors[ i ];

        CrReflector* crReflector = GetAssetManager()->Get< CrReflector >( ECrAssetType::Reflector, reflector[ "Mesh" ].GetString() );
        
        crReflector->SetWidth    ( reflector[ "Width"     ].GetInt() );
        crReflector->SetHeight   ( reflector[ "Height"    ].GetInt() );
        crReflector->SetIntensity( reflector[ "Intensity" ].GetFloat() );

        Reflectors.push_back( crReflector );
    }

}
