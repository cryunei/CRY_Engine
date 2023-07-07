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
        // Assuming triangles, so process only the first three vertices of each polygon
        for ( int j = 0; j < 3; ++j )
        {
            int controlPointIndex = fbxMesh->GetPolygonVertex( i, j );
            Vertex vertex;

            // Set the position
            vertex.Position.x = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 0 ] );
            vertex.Position.y = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 1 ] );
            vertex.Position.z = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 2 ] );

            _ReadNormal( fbxMesh, controlPointIndex, idx, vertex.Normal );

            // Set the texture coordinates (if available)
            if ( hasUVs )
            {
                int uvIndex = fbxUVs->GetIndexArray().GetAt( controlPointIndex );
                const FbxVector2& uv = fbxUVs->GetDirectArray().GetAt( uvIndex );
                vertex.TextureUV.x = static_cast< float >( uv[ 0 ] );
                vertex.TextureUV.y = static_cast< float >( uv[ 1 ] );
            }

            // Add the vertex to the output vector
            OutVertices.push_back( vertex );
            OutIndices.push_back( idx++ );
        }
    }
}

//=================================================================================================
// @brief	Read normal
//=================================================================================================
void FbxImportHelper::_ReadNormal( FbxMesh* Mesh, int ControlPointIndex, int VertexCounter, XMFLOAT3& OutNormal ) const
{
    if ( !Mesh ) return;
    if ( Mesh->GetElementNormalCount() < 1 ) return;

    int idx = ControlPointIndex;

    FbxGeometryElementNormal* normal = Mesh->GetElementNormal( 0 );
    switch ( normal->GetMappingMode() )
    {
    case FbxGeometryElement::eByControlPoint:  idx = ControlPointIndex; break;
    case FbxGeometryElement::eByPolygonVertex: idx = VertexCounter; break;
    default: break;
    }

    if ( normal->GetReferenceMode() == FbxGeometryElement::eIndexToDirect )
    {
        idx = normal->GetIndexArray().GetAt( idx );
    }

    OutNormal.x = static_cast< float >( normal->GetDirectArray().GetAt( idx ).mData[ 0 ] );
    OutNormal.y = static_cast< float >( normal->GetDirectArray().GetAt( idx ).mData[ 1 ] );
    OutNormal.z = static_cast< float >( normal->GetDirectArray().GetAt( idx ).mData[ 2 ] );
}

