#include "FbxImportHelper.h"
#include "../Asset/CrAssetManager.h"
#include "../Asset/CrVertexBuffer.h"


//=================================================================================================
// @brief	Constructor
//=================================================================================================
FbxImportHelper::FbxImportHelper()
: FbxManager    ( nullptr )
, FbxIOSettings ( nullptr )
, FbxImporter   ( nullptr )
, FbxScene      ( nullptr )
{
}

//=================================================================================================
// @brief	Clear
//=================================================================================================
void FbxImportHelper::Clear()
{
    if ( FbxManager )
    {
        FbxManager->Destroy();
        FbxManager = nullptr;
    }

    FbxIOSettings = nullptr;
    FbxImporter   = nullptr;
    FbxScene      = nullptr;
}

//=================================================================================================
// @brief	Load
//=================================================================================================
bool FbxImportHelper::Load( const std::string& FilePath )
{
    Clear();

    FbxManager = FbxManager::Create();
    if ( !FbxManager ) return false;

    FbxIOSettings = FbxIOSettings::Create( FbxManager, IOSROOT );
    if ( !FbxIOSettings ) return false;

    FbxManager->SetIOSettings( FbxIOSettings );
    
    FbxImporter = FbxImporter::Create( FbxManager, "" );
    if ( !FbxImporter ) return false;

    FbxImporter->Initialize( FilePath.c_str(), -1, FbxManager->GetIOSettings() );
    
    FbxScene = FbxScene::Create( FbxManager, "" );
    FbxImporter->Import( FbxScene );
    FbxImporter->Destroy();

    return true;
}

//=================================================================================================
// @brief	Load All
//=================================================================================================
bool FbxImportHelper::LoadAll( const std::string& FilePath, const std::string& AssetName )
{
    Load( FilePath );

    if ( !FbxScene ) return false;

    FbxNode* fbxRootNode = FbxScene->GetRootNode();
    if ( !fbxRootNode ) return false;

    int childCount = fbxRootNode->GetChildCount();

    for ( int i = 0; i < childCount; ++i )
    {
        // load mesh
        FbxNode* fbxMeshNode = fbxRootNode->GetChild( i );
        if ( !fbxMeshNode ) continue;

        FbxMesh* fbxMesh = fbxMeshNode->GetMesh();
        if ( !fbxMesh ) continue;

        CrVertexBuffer* vb = GetAssetManager()->CreateVertexBuffer( AssetName + "_Vertex" + std::to_string( i ) );
        if ( !vb ) break;

        vb->Vertices.reserve( _GetVertexCount( fbxMesh ) );

        // Process each polygon
        for ( int i = 0; i < fbxMesh->GetPolygonCount(); ++i )
        {
            _AddVertex( fbxMesh, i, 0, vb->Vertices );
            _AddVertex( fbxMesh, i, 1, vb->Vertices );
            _AddVertex( fbxMesh, i, 2, vb->Vertices );

            for ( int j = 2; j < fbxMesh->GetPolygonSize( i ); ++j )
            {
                _AddVertex( fbxMesh, i, 0    , vb->Vertices );
                _AddVertex( fbxMesh, i, j    , vb->Vertices );
                _AddVertex( fbxMesh, i, j + 1, vb->Vertices );
            }
        }
    }

    return true;
}

//=================================================================================================
// @brief	Add vertex
//=================================================================================================
void FbxImportHelper::_AddVertex( FbxMesh* Mesh, int ControlPointIndex, int PositionPolygon, std::vector< Vertex >& OutVertices ) const
{
    if ( !Mesh ) return;

    Vertex vtx;

    FbxVector4* fbxVertices = Mesh->GetControlPoints();
    int controlPointIndex = Mesh->GetPolygonVertex( ControlPointIndex, PositionPolygon );

    vtx.Position.x = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 0 ] );
    vtx.Position.y = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 1 ] );
    vtx.Position.z = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 2 ] );

    FbxVector4 normal;
    Mesh->GetPolygonVertexNormal( ControlPointIndex, PositionPolygon, normal );

    vtx.Normal.x = static_cast< float >( normal.mData[ 0 ] );
    vtx.Normal.y = static_cast< float >( normal.mData[ 1 ] );
    vtx.Normal.z = static_cast< float >( normal.mData[ 2 ] );

    FbxVector2 uv;
    bool unmappedUV;
    Mesh->GetPolygonVertexUV( ControlPointIndex, PositionPolygon, Mesh->GetElementUV( 0 )->GetName(), uv, unmappedUV );
    if ( !unmappedUV )
    {
        vtx.TextureUV.x = static_cast< float >( uv.mData[ 0 ] );
        vtx.TextureUV.y = static_cast< float >( uv.mData[ 1 ] );
    }

    OutVertices.push_back( vtx );
}

//=================================================================================================
// @brief	Get vertex count
//=================================================================================================
int FbxImportHelper::_GetVertexCount( FbxMesh* Mesh ) const
{
    if ( !Mesh ) return 0;

    int count = 0;
    // Process each polygon
    for ( int i = 0; i < Mesh->GetPolygonCount(); ++i )
    {
        count += 3;
        for ( int j = 2; j < Mesh->GetPolygonSize( i ); ++j )
        {
            count += 3;
        }
    }

    return count;
}
