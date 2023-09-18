#pragma once


#include "Dx11RenderTypes.h"
#include "../Core/Dx11RenderTarget.h"


class CrCamera;
class Dx11ConstantBuffer;
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
    Dx11RenderTarget*     RenderTargetPtr;
    MeshRenderElementList MeshRenderElements;
    RenderElementList     RenderElements;

public:
    // Construct
    Dx11RenderQueue();

    // Initialize render target
    void InitializeRenderTarget( const std::string& RenderTargetName );

    // Set camera
    void SetCamera( CrCamera* InCameraPtr ) { CameraPtr = InCameraPtr; }

    // Add
    bool Add( const Dx11Mesh* MeshePtr, const Dx11ConstantBuffer* WorldBufferPtr, const Dx11ConstantBuffer* RenderPropertyBufferPtr );

    // Clear
    void Clear();

    // Sort
    void Sort();

    // Render
    void Render() const;

    // Getter
    Dx11RenderTarget* GetRenderTarget() { return RenderTargetPtr; }
    CrCamera* GetCamera() const { return CameraPtr; }
    unsigned int GetViewportWidth() const { return (unsigned int)( RenderTargetPtr->GetViewport().Width ); }
    unsigned int GetViewportHeight() const { return (unsigned int)( RenderTargetPtr->GetViewport().Height ); }

};
