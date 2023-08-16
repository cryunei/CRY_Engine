#pragma once


#include "Dx11Primitive.h"
#include "Dx11Material.h"
#include "../Core/DxTransform.h"


//=====================================================================================================================
// @brief	Dx11Mesh
//=====================================================================================================================
class Dx11Mesh
{
private:
    DxTransform   Transform;
    Dx11Primitive Primitive;
    Dx11Material  Material;

public:
    // Construct
    Dx11Mesh() = default;

    // Initialize primitive
    void InitializePrimitive( Dx11VertexBuffer* VB, Dx11IndexBuffer* IB ) { Primitive.Initialize( VB, IB ); }

    // Initialize material
    void InitializeMaterial( Dx11VertexShader* VS, Dx11PixelShader* PS ) { Material.Initialize( VS, PS ); }

    // Initialize texture 2d array
    void InitializeTexture2Ds( const std::vector< Dx11Texture2D* >& InTexture2Ds ) { Material.InitializeTexture2Ds( InTexture2Ds ); }

    // Get transform
    const DxTransform& GetTransform() const { return Transform; }
    DxTransform& GetTransform() { return Transform; }

    // Get primitive
    const Dx11Primitive& GetPrimitive() const { return Primitive; }
    Dx11Primitive& GetPrimitive() { return Primitive; }

    // Get material
    const Dx11Material& GetMaterial() const { return Material; }
    Dx11Material& GetMaterial() { return Material; }
};