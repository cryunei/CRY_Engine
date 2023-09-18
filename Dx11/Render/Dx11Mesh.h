#pragma once


#include "Dx11Primitive.h"
#include "Dx11Material.h"
#include "../Core/DxTransform.h"
#include <string>


//=====================================================================================================================
// @brief	Dx11Mesh
//=====================================================================================================================
class Dx11Mesh
{
private:
    DxTransform   Transform;
    Dx11Primitive Primitive;
    Dx11Material  Material;

    std::string   RenderTarget;
    float         Opacity;

public:
    // Construct
    Dx11Mesh() = default;

    // Initialize primitive
    void InitializePrimitive( Dx11VertexBuffer* VB, Dx11IndexBuffer* IB ) { Primitive.Initialize( VB, IB ); }

    // Initialize material
    void InitializeMaterial( Dx11VertexShader* VS, Dx11PixelShader* PS ) { Material.Initialize( VS, PS ); }

    // Initialize texture 2d array
    void InitializeTexture2Ds( const std::vector< Dx11ResourceRenderer* >& InResourceRenderers ) { Material.InitializeTexture2Ds( InResourceRenderers ); }

    // Incrase render count
    void IncreaseRenderCount() const { Primitive.IncreaseRenderCount(); Material.IncreaseRenderCount(); }

    // Decrease render count
    void DecreaseRenderCount() const { Primitive.DecreaseRenderCount(); Material.DecreaseRenderCount(); }

    // Get transform
    const DxTransform& GetTransform() const { return Transform; }
    DxTransform& GetTransform() { return Transform; }
    void SetTransform( const DxTransform& InTransform ) { Transform = InTransform; }

    // Get primitive
    const Dx11Primitive& GetPrimitive() const { return Primitive; }
    Dx11Primitive& GetPrimitive() { return Primitive; }

    // Get material
    const Dx11Material& GetMaterial() const { return Material; }
    Dx11Material& GetMaterial() { return Material; }

    // Render target
    const std::string& GetRenderTarget() const { return RenderTarget; }
    void SetRenderTarget( const std::string& InRenderTarget ) { RenderTarget = InRenderTarget; }

    // Ocaticy
    float GetOpacity() const { return Opacity; }
    void SetOpacity( float InOpacity ) { Opacity = InOpacity; }
};