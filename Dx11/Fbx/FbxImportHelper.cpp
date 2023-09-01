#include "FbxImportHelper.h"
#include "../Asset/CrAssetManager.h"
#include "../Asset/CrPrimitive.h"
#include "../Render/Dx11VertexStructure.h"


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

        CrPrimitive* primitive = GetAssetManager()->CreatePrimitive( AssetName + "_Primitive" + std::to_string( i ) );
        if ( !primitive ) break;

        int vertexCount = _getVertexCount( fbxMesh );

        primitive->Reserve( vertexCount );

        Vector3 location[ 3 ];
        Vector3 normal  [ 3 ];
        Vector3 tangent [ 3 ];
        Vector3 binormal[ 3 ];
        Vector2 uv      [ 3 ];

        auto ftrAddElements = [ this, &fbxMesh, &primitive, &location, &normal, &tangent, &binormal, &uv ] ( int p, const int (&polygonIdx)[ 3 ] )
        {
            _getLocation( fbxMesh, p, polygonIdx, location );
            _getUV      ( fbxMesh, p, polygonIdx, uv       );
            _getNormal  ( fbxMesh, p, polygonIdx, normal   );

            primitive->Locations.insert( primitive->Locations.end(), location, location + 3 );
            primitive->UVs      .insert( primitive->UVs      .end(), uv,       uv       + 3 );
            primitive->Normals  .insert( primitive->Normals  .end(), normal,   normal   + 3 );

            _getTangentAndBitangents( location, uv, tangent, binormal );

            primitive->Tangents .insert( primitive->Tangents .end(), tangent , tangent  + 3 );
            primitive->Bitangents.insert( primitive->Bitangents.end(), binormal, binormal + 3 );
        };

        // Process each polygon
        int polygonIdx[ 3 ] = { 0, 1, 2 };
        for ( int p = 0; p < fbxMesh->GetPolygonCount(); ++p )
        {
            int polygonSize = fbxMesh->GetPolygonSize( i );
            if ( polygonSize < 3 ) continue;

            ftrAddElements( p, polygonIdx );

            if ( polygonSize <= 3 ) continue;

            for ( int e = 2; e < polygonSize; ++e )
            {
                int polygonIdxEx[ 3 ] = { 0, e, e + 1 };
                ftrAddElements( p, polygonIdxEx );
            }
        }
    }

    return true;
}

//=====================================================================================================================
// @brief	Get location
//=====================================================================================================================
void FbxImportHelper::_getLocation( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector3 (&OutLocations)[ 3 ] ) const
{
    for ( int i = 0; i < 3; ++i )
    {
        FbxVector4* fbxVertices = Mesh->GetControlPoints();
        int controlPointIndex = Mesh->GetPolygonVertex( ControlPointIndex, PositionPolygon[ i ] );

        OutLocations[ i ].x = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 0 ] );
        OutLocations[ i ].y = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 1 ] );
        OutLocations[ i ].z = static_cast< float >( fbxVertices[ controlPointIndex ].mData[ 2 ] );
    }    
}

//=====================================================================================================================
// @brief	Get UV
//=====================================================================================================================
void FbxImportHelper::_getUV( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector2 (&OutUVs)[ 3 ] ) const
{
    int uvCount = Mesh->GetElementUVCount();
    for ( int i = 0; i < uvCount; ++i )
    {
        const char* name = Mesh->GetElementUV( i )->GetName();
    }

    for ( int i = 0; i < 3; ++i )
    {
        FbxVector2 uv;
        bool unmappedUV;
        Mesh->GetPolygonVertexUV( ControlPointIndex, PositionPolygon[ i ], Mesh->GetElementUV( 0 )->GetName(), uv, unmappedUV );
        if ( !unmappedUV )
        {
            OutUVs[ i ].x = static_cast< float >( uv.mData[ 0 ] );
            OutUVs[ i ].y = static_cast< float >( uv.mData[ 1 ] );
        }
    }
}

//=====================================================================================================================
// @brief	Get normal
//=====================================================================================================================
void FbxImportHelper::_getNormal( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector3 (&OutNormals)[ 3 ] ) const
{
    for ( int i = 0; i < 3; ++i )
    {
        FbxVector4 normal;
        Mesh->GetPolygonVertexNormal( ControlPointIndex, PositionPolygon[ i ], normal );

        OutNormals[ i ].x = static_cast< float >( normal.mData[ 0 ] );
        OutNormals[ i ].y = static_cast< float >( normal.mData[ 1 ] );
        OutNormals[ i ].z = static_cast< float >( normal.mData[ 2 ] );
    }
}

//=====================================================================================================================
// @brief	Get tangent and bitangent
//=====================================================================================================================
void FbxImportHelper::_getTangentAndBitangents( const Vector3 (&Location)[ 3 ], const Vector2 (&UVs)[ 3 ], Vector3 (&OutTangents)[ 3 ], Vector3 (&OutBitangents)[ 3 ] ) const
{
    Vector3 edge1 = Location[ 1 ] - Location[ 0 ];
    Vector3 edge2 = Location[ 2 ] - Location[ 0 ];

    Vector2 deltaUV1 = UVs[ 1 ] - UVs[ 0 ];
    Vector2 deltaUV2 = UVs[ 2 ] - UVs[ 0 ];

    float f = 1.0f / ( deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y );

    OutTangents[ 0 ] = f * ( deltaUV2.x * edge1 - deltaUV1.x * edge2 );
    OutTangents[ 0 ].Normalize();

    OutTangents[ 1 ] =OutTangents[ 2 ] = OutTangents[ 0 ];

    OutBitangents[ 0 ] = f * ( -deltaUV2.y * edge1 + deltaUV1.y * edge2 );
    OutBitangents[ 0 ].Normalize();

    OutBitangents[ 1 ] = OutBitangents[ 2 ] = OutBitangents[ 0 ];
}

//=================================================================================================
// @brief	Get vertex count
//=================================================================================================
int FbxImportHelper::_getVertexCount( FbxMesh* Mesh ) const
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
