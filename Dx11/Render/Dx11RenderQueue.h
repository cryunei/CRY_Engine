#pragma once


#include "Dx11RenderTypes.h"


class Dx11Mesh;
class IDxRenderElement;
class IDxRenderQueueCandidate;


//=====================================================================================================================
// @brief	Dx11RenderQueue
//=====================================================================================================================
class Dx11RenderQueue
{
private:
    MeshRenderElementList MeshRenderElements;
    RenderElementList     RenderElements;

public:
    // Construct
    Dx11RenderQueue();

    // Add
    bool Add( const Dx11Mesh* MeshePtr, const WorldMatrixBuffer* WorldBufferPtr );

    // Clear
    void Clear();

    // Sort
    void Sort();

    // Render
    void Render() const;

};
