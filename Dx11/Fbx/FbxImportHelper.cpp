#include "FbxImportHelper.h"


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
// @brief	Get vertices
//=================================================================================================
void FbxImportHelper::GetVertices( std::vector< Vertex >& OutVertices, std::vector< int >& OutIndices ) const
{
    if ( !FbxScene ) return;

    FbxNode* fbxRootNode = FbxScene->GetRootNode();

    // load mesh
    FbxNode* fbxMeshNode = fbxRootNode->GetChild( 0 );
    if ( !fbxMeshNode ) return;

    FbxMesh* fbxMesh = fbxMeshNode->GetMesh();
    if ( !fbxMesh ) return;
    
    // Get the vertex positions
    FbxVector4* fbxVertices = fbxMesh->GetControlPoints();

    // Get the vertex normals (if available)
    FbxGeometryElementNormal* fbxNormals = fbxMesh->GetElementNormal();
    bool hasNormals = fbxNormals && fbxNormals->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;

    // Get the texture coordinates (if available)
    FbxGeometryElementUV* fbxUVs = fbxMesh->GetElementUV();
    bool hasUVs = fbxUVs && fbxUVs->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;

    // Process each polygon
    int idx = 0;
    for ( int i = 0; i < fbxMesh->GetPolygonCount(); ++i )
    {
        _AddVertex( fbxMesh, i, 0, OutVertices );
        _AddVertex( fbxMesh, i, 1, OutVertices );
        _AddVertex( fbxMesh, i, 2, OutVertices );

        for ( int j = 2; j < fbxMesh->GetPolygonSize( i ); ++j )
        {
            _AddVertex( fbxMesh, i, 0    , OutVertices );
            _AddVertex( fbxMesh, i, j    , OutVertices );
            _AddVertex( fbxMesh, i, j + 1, OutVertices );
        }
    }
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