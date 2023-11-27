#pragma once


#include "Dx11RenderQueue.h"
#include "../Core/Dx11ConstantBuffer.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Actor/Light/CrDirectionalLight.h"
#include "../Core/Dx11RenderTarget.h"
#include "../Render/Dx11ConstantBufferStructure.h"
#include <map>


#pragma comment ( lib, "d3d11.lib" )


//=====================================================================================================================
// @brief	Dx11Renderer
//=====================================================================================================================
class Dx11Renderer
{
private:
	float ViewportWidth;
	float ViewportHeight;

	ComPtr< ID3D11BlendState > BlendStateComPtr;

	std::map< std::string, Dx11RenderQueue > RenderToTextureQueues;
	Dx11RenderQueue RenderQueueScreen;
	Dx11RenderQueue BlendedRenderQueueScreen;

	CrCamera Camera;
	CrCamera Camera_RT;
	CrDirectionalLight Light;

public:
	// Constructor
	Dx11Renderer();

	// Clear
	void Clear();
	
	// Initialize
	void Initialize( int Width, int Height );

	// Add render target
	void AddRenderTarget( const std::string& RenderTargetName, int Width, int Height, DXGI_FORMAT Format );

	// Render frame
	void RenderFrame();

	// Add mesh render element
	bool AddMeshRenderElement( const CrMeshActor& MeshActor );
	
	// Add mesh render element
	bool AddMeshRenderElement( const CrMeshActor& MeshActor, const std::string& RenderTargetName );

	// Sort render queue	
	void SortRenderQueue();

	// Change blend state
	void ChangeBlendState( D3D11_BLEND SrcBlend, D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcBlendAlpha, D3D11_BLEND DestBlendAlpha, D3D11_BLEND_OP BlendOpAlpha );

	// Enable blend state
	void EnableBlendState() const;

	// Disable blend state
	void DisableBlendState() const;

	// Camera
	CrCamera* GetCamera() { return &Camera; }
	const CrCamera* GetCamera() const { return &Camera; }

	// Light
	CrDirectionalLight* GetLight() { return &Light; }
	void SetLightDirection( const Vector3& Direction );

	// Render queue
	Dx11RenderQueue* GetRenderToTextureQueue( const std::string& RenderTargetName );
	Dx11RenderTarget* GetRenderTarget( const std::string& RenderTargetName );

private:
	// Set view projection matrix buffer data
	void _setViewProjectionMatrixBufferData( const CrCamera* Camera, unsigned int InViewportWidth, unsigned int InViewportHeight ) const;

	// Set light property buffer data
	void _setLightPropertyBufferData() const;
};

