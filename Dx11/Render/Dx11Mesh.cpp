#include "Dx11Mesh.h"

//=================================================================================================
// @brief	Constructor
//=================================================================================================
Dx11Mesh::Dx11Mesh()
{
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Mesh::Initialize()
{
    Primitive.Initialize();
    Primitive.LoadFBX( "../Asset/Fbx/tower.fbx" );
    Material .Initialize();

    // Test code
    Transform.SetLocationY( -10.f );
    Transform.SetLocationX(  15.f );
    //Transform.SetRotationX( 1.57f );
    //Transform.SetRotationY( -1.57f );
    Transform.SetScale( 0.5f, 0.5f, 0.5f );
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Mesh::Render()
{
    Material .Render();
    Primitive.Render();
}
