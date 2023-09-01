#pragma once


#include <vector>


class Dx11Renderer;
class CrLevel;
class Dx11Mesh;


class Dx11LevelLoader
{
private:
    std::vector< Dx11Mesh* > Meshes;
    Dx11Mesh*                TestMesh;
    Dx11Mesh*                TestRT;

public:
    // Load
    void Load( class CrLevel& InLevel );

    // Add render meshes
    void AddRenderMeshes( Dx11Renderer& InRenderer ) const;
    
};
