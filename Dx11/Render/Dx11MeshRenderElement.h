#pragma once


#include "Dx11RenderElement.h"


class Dx11ConstantBuffer;
class Dx11Mesh;


//=====================================================================================================================
// @brief	Dx11MeshRenderElement
//=====================================================================================================================
class Dx11MeshRenderElement : public Dx11RenderElement
{
private:
    const Dx11Mesh* MeshPtr;
    const Dx11ConstantBuffer* WorldBufferPtr;
    const Dx11ConstantBuffer* RenderPropertyBufferPtr;

public:
    // Construct
    Dx11MeshRenderElement( const Dx11Mesh* InMeshPtr, const Dx11ConstantBuffer* InWorldBufferPtr, const Dx11ConstantBuffer* InRenderPropertyBufferPtr )
    : MeshPtr( InMeshPtr ) , WorldBufferPtr( InWorldBufferPtr ), RenderPropertyBufferPtr( InRenderPropertyBufferPtr )
    {}

    // On render
    virtual void OnRender() const override;
};