#include "Dx11Mesh.h"
#include "../Core/Dx11ResourceManager.h"

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
    Dx11VertexShader* dxVS = GetDx11ResourceManager()->CreateVertexShader( "DefaultDiffuse" );
    Dx11PixelShader*  dxPS = GetDx11ResourceManager()->CreatePixelShader( "HalfLambert" );

    Dx11VertexBuffer* dxVB  = GetDx11ResourceManager()->CreateVertexBuffer( "WoodenSphere_Vertex0" );    
    Dx11Texture2D*    dxTex = GetDx11ResourceManager()->CreateTexture2D( "WoodenSphereDiffuse" );

    Primitive.Initialize( dxVB, nullptr, dxVS );    
    Material .Initialize( dxPS, dxTex );

    // Test code
    //Transform.SetLocationY( -10.f );
    //Transform.SetLocationX(  15.f );
    //Transform.SetRotationX( 1.57f );
    //Transform.SetRotationY( -1.57f );
    Transform.SetScale( 2.f, 2.f, 2.f );
    //Transform.SetScale( 0.5f, 0.5f, 0.5f );
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Mesh::Render()
{
    Material .Render();
    Primitive.Render();
}
