#pragma once


#include "Dx11RenderQueue.h"
#include "../Core/Dx11ConstantBuffer.h"
#include "../Render/Dx11Mesh.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Actor/Light/CrDirectionalLight.h"
#include "../Render/Dx11ConstantBufferStructure.h"
#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


//=====================================================================================================================
// @brief	Dx11Renderer
//=====================================================================================================================
class Dx11Renderer
{
private:
	float ViewportWidth;
	float ViewportHeight;

	ID3D11RenderTargetView* RenderTargetView;

	WorldMatrixBuffer        WorldBuffer;
	ViewProjMatrixBuffer     ViewProjBuffer;
	CameraPropertyBuffer     CameraBuffer;
	LightPropertyBuffer      LightBuffer;
	SpecularPropertyBuffer   SpecularBuffer;
	PointLightLocationBuffer LightLocationBuffer;
	PointLightColorBuffer    LightColorBuffer;

	Dx11RenderQueue RenderQueue;

	CrCamera Camera;
	CrDirectionalLight Light;

public:
	// Constructor
	Dx11Renderer();

	// Clear
	void Clear();
	
	// Initialize
	void Initialize( int Width, int Height );

	// Render frame
	void RenderFrame();

	// Add mesh render element
	bool AddMeshRenderElement( const Dx11Mesh* MeshPtr );

	// Sort render queue	
	void SortRenderQueue();

	CrCamera* GetCamera() { return &Camera; }
	const CrCamera* GetCamera() const { return &Camera; }

	CrDirectionalLight* GetLight() { return &Light; }
	void SetLightDirection( const Vector3& Direction );

private:
	// Initialize render target view
	void _initializeRenderTargetView();

	// Initialize viewport
	void _initializeViewport( int Width, int Height );

	// Initialize constant buffers
	void _initializeConstantBuffers();

	// Set view projection matrix buffer data
	void _setViewProjectionMatrixBufferData() const;

	// Set light property buffer data
	void _setLightPropertyBufferData() const;
};

