#pragma once

#include "Dx11Material.h"
#include "Dx11Primitive.h"
#include "Dx11RenderElement.h"
#include "../Core/DxTransform.h"

class Dx11ConstantBuffer;
class Dx11Mesh;


//=====================================================================================================================
// @brief	Dx11MeshRenderElement
//=====================================================================================================================
class Dx11MeshRenderElement : public Dx11RenderElement
{
private:
    friend class Dx11RenderQueue;

protected:
    const DxTransform*      Transform    = nullptr;
    const Dx11IndexBuffer*  IndexBuffer  = nullptr;
    const Dx11VertexShader* VertexShader = nullptr;
    const Dx11PixelShader*  PixelShader  = nullptr;
    const Dx11VertexBuffer* VertexBuffer = nullptr;
    float                   Opacity      = 1.f;

    std::vector< Dx11ResourceRenderer* > Texture2Ds;

public:
    // Construct
    Dx11MeshRenderElement() = default;

    // On render
    virtual void OnRender() const override;
};