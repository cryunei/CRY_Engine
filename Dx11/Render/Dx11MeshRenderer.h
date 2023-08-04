#pragma once

#include "Dx11ConstantBufferStructure.h"
#include "Dx11MeshRenderer.h"
#include "../Core/IDxRenderElement.h"


class Dx11Mesh;


class Dx11MeshRenderer : public IDxRenderElement
{
private:
    const Dx11Mesh* MeshPtr;
    const WorldMatrixBuffer* WorldBufferPtr;

public:
    // Construct
    Dx11MeshRenderer( const Dx11Mesh* InMeshPtr, const WorldMatrixBuffer* InWorldBufferPtr )
    : MeshPtr( InMeshPtr )
    , WorldBufferPtr( InWorldBufferPtr )
    {}

    // On render
    virtual void OnRender() const override;
};