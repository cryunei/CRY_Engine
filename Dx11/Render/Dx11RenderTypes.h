#pragma once


#include "Dx11MeshRenderer.h"
#include <vector>


class IDxRenderElement;
class Dx11Mesh;


//=====================================================================================================================
// @brief	MeshRenderELement
//=====================================================================================================================
struct MeshRenderElement
{
    const Dx11Mesh*  MeshPtr;
    Dx11MeshRenderer Renderer;

    // Construct
    MeshRenderElement( const Dx11Mesh* InMeshPtr, const WorldMatrixBuffer* InWorldBufferPtr )
    : MeshPtr( InMeshPtr )
    , Renderer( InMeshPtr, InWorldBufferPtr )
    {}
};


using RenderElementList = std::vector< const IDxRenderElement* >;
using MeshRenderElementList = std::vector< MeshRenderElement >;