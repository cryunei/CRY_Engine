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
    // Read normal
    void _ReadNormal( FbxMesh* Mesh, int ControlPointIndex, int VertexCounter, XMFLOAT3& OutNormal ) const;
};
