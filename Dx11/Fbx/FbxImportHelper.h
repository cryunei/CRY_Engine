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

    // Get vertices
    void GetVertices( std::vector< Vertex >& OutVertices, std::vector< int >& OutIndices ) const;

private:
    // Add vertex
    void _AddVertex( FbxMesh* Mesh, int ControlPointIndex, int PositionPolygon, std::vector< Vertex >& OutVertices ) const;
};
