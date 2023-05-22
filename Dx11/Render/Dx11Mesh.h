#pragma once

#include <DirectXMath.h>
#include "Dx11Primitive.h"
#include "Dx11Material.h"
#include "../Core/DxTransform.h"


#pragma comment ( lib, "d3d11.lib" )
#pragma comment ( lib, "d3dcompiler.lib" )


using namespace DirectX;


class Dx11Mesh
{
private:
    DxTransform   Transform;
    Dx11Primitive Primitive;
    Dx11Material  Material;

public:
    // Constructorride
    Dx11Mesh();

    // Initialize
    void Initialize();

    // Render
    void Render();
};