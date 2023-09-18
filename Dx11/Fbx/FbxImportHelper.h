#pragma once


#include "../DxTypes.h"
#include <fbxsdk.h>


#pragma comment ( lib, "libfbxsdk.lib" )


//=====================================================================================================================
// @brief	FbxImportHelper
//=====================================================================================================================
class FbxImportHelper
{
private:
    FbxManager*    FbxManager;
    FbxIOSettings* FbxIOSettings;
    FbxImporter*   FbxImporter;
    FbxScene*      FbxScene;
    
public:
    // Constructor
    FbxImportHelper();

    // Clear
    void Clear();

    // Load
    bool Load( const std::string& FilePath );

    // Load All
    bool LoadAll( const std::string& FilePath, const std::string& AssetName );

private:
    // Get location
    void _getLocation( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector3 (&OutLocations)[ 3 ] ) const;

    // Get UV
    void _getUV( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector2 (&OutUVs)[ 3 ] ) const;

    // Get normal
    void _getNormal( FbxMesh* Mesh, int ControlPointIndex, const int (&PositionPolygon)[ 3 ], Vector3 (&OutNormals)[ 3 ] ) const;

    // Get vertex count
    int _getVertexCount( FbxMesh* Mesh ) const;
};


