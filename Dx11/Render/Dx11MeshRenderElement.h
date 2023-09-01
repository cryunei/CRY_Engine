#pragma once


#include "Dx11ConstantBufferStructure.h"
#include "Dx11RenderElement.h"


class Dx11Mesh;


//=====================================================================================================================
// @brief	Dx11MeshRenderElement
//=====================================================================================================================
class Dx11MeshRenderElement : public Dx11RenderElement
{
private:
    const Dx11Mesh* MeshPtr;
    const WorldMatrixBuffer* WorldBufferPtr;

public:
    // Construct
    Dx11MeshRenderElement( const Dx11Mesh* InMeshPtr, const WorldMatrixBuffer* InWorldBufferPtr )
    : MeshPtr( InMeshPtr )
    , WorldBufferPtr( InWorldBufferPtr )
    {}

    // On render
    virtual void OnRender() const override;
};