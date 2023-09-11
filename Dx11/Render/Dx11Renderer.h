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

	Dx11ConstantBuffer* WorldBuffer;
	Dx11ConstantBuffer* ViewProjBuffer;
	Dx11ConstantBuffer* CameraBuffer;
	Dx11ConstantBuffer* LightBuffer;
	Dx11ConstantBuffer* SpecularBuffer;
	Dx11ConstantBuffer* LightLocationBuffer;
	Dx11ConstantBuffer* LightColorBuffer;

	std::map< std::string, Dx11RenderQueue > RenderQueues;
	Dx11RenderQueue RenderQueueScreen; 

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
	bool AddMeshRenderElement( const Dx11Mesh* MeshPtr );
	
	// Add mesh render element
	bool AddMeshRenderElement( const Dx11Mesh* MeshPtr, const std::string& RenderTargetName );

	// Sort render queue	
	void SortRenderQueue();

	CrCamera* GetCamera() { return &Camera; }
	const CrCamera* GetCamera() const { return &Camera; }

	CrDirectionalLight* GetLight() { return &Light; }
	void SetLightDirection( const Vector3& Direction );

	Dx11RenderQueue* GetRenderQueue( const std::string& RenderTargetName );
	Dx11RenderTarget* GetRenderTarget( const std::string& RenderTargetName );

private:
	// Initialize constant buffers
	void _initializeConstantBuffers();

	// Set view projection matrix buffer data
	void _setViewProjectionMatrixBufferData( const CrCamera* Camera, unsigned int InViewportWidth, unsigned int InViewportHeight ) const;

	// Set light property buffer data
	void _setLightPropertyBufferData() const;
};

