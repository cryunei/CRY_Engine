#pragma once


#include "Dx11MeshRenderElement.h"
#include "DirectXTK/Inc/BufferHelpers.h"
#include <vector>


class IDxRenderElement;
class Dx11Mesh;


//=====================================================================================================================
// @brief	MeshRenderELement
//=====================================================================================================================
struct MeshRenderElement
{
    const Dx11Mesh*  MeshPtr;
    Dx11MeshRenderElement Renderer;

    // Construct
    MeshRenderElement( const Dx11Mesh* InMeshPtr, const Dx11ConstantBuffer* InWorldBufferPtr, const Dx11ConstantBuffer* InRenderPropertyBufferPtr )
    : MeshPtr( InMeshPtr )
    , Renderer( InMeshPtr, InWorldBufferPtr, InRenderPropertyBufferPtr )
    {}
};


using RenderElementList = std::vector< const IDxRenderElement* >;
using MeshRenderElementList = std::vector< MeshRenderElement >;