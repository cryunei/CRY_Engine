#pragma once


#include "../DxTypes.h"
#include <fbxsdk.h>


#pragma comment ( lib, "libfbxsdk.lib" )


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
    // Add vertex
    void _AddVertex( FbxMesh* Mesh, int ControlPointIndex, int PositionPolygon, std::vector< Vertex >& OutVertices ) const;

    // Get vertex count
    int _GetVertexCount( FbxMesh* Mesh ) const;
};
