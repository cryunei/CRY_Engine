#pragma once


#include "Dx11RenderTypes.h"
#include "../Core/Dx11RenderTarget.h"

class CrCamera;
class Dx11Mesh;
class IDxRenderElement;
class IDxRenderQueueCandidate;


//=====================================================================================================================
// @brief	Dx11RenderQueue
//=====================================================================================================================
class Dx11RenderQueue
{
private:
    CrCamera*             CameraPtr;
    Dx11RenderTarget      RenderTarget;
    MeshRenderElementList MeshRenderElements;
    RenderElementList     RenderElements;

public:
    // Construct
    Dx11RenderQueue();

    // Initialize 
    void Initialize( unsigned int Width, unsigned int Height );

    // Set camera
    void SetCamera( CrCamera* InCameraPtr ) { CameraPtr = InCameraPtr; }

    // Add
    bool Add( const Dx11Mesh* MeshePtr, const WorldMatrixBuffer* WorldBufferPtr );

    // Clear
    void Clear();

    // Sort
    void Sort();

    // Render
    void Render() const;

    // Getter
    Dx11RenderTarget* GetRenderTarget() { return &RenderTarget; }
    CrCamera* GetCamera() const { return CameraPtr; }
    unsigned int GetViewportWidth() const { return RenderTarget.GetViewport().Width; }
    unsigned int GetViewportHeight() const { return RenderTarget.GetViewport().Height; }

};
