#pragma once

#include "Dx11ConstantBuffer.h"
#include "../Render/Dx11Mesh.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Actor/Light/CrDirectionalLight.h"
#include "../Render/Dx11ConstantBufferStructure.h"
#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


class Dx11Renderer
{
private:
	ID3D11RenderTargetView*              RenderTargetView;
	Dx11ConstantBuffer< WorldMatrix >    WorldMatrixBuffer;
	Dx11ConstantBuffer< ViewProjMatrix > ViewProjectionMatrixBuffer;
	Dx11ConstantBuffer< LightProperty >  LightPropertyBuffer;	

	float ViewportWidth;
	float ViewportHeight;

	Dx11Mesh Mesh;
	CrCamera Camera;
	CrDirectionalLight Light;

public:
	// Constructor
	Dx11Renderer();

	// Clear
	void Clear();
	
	// Initialize
	void Initialize();

	// Render frame
	void RenderFrame();

	CrCamera* GetCamera() { return &Camera; }
	const CrCamera* GetCamera() const { return &Camera; }

private:
	// Initialize render target view
	void _initializeRenderTargetView();

	// Initialize viewport
	void _initializeViewport() const;

	// Initialize constant buffers
	void _initializeConstantBuffers();

	// Set world matrix buffer data
	void _setWorldMatrixBufferData( const XMMATRIX& Matrix ) const;

	// Set view projection matrix buffer data
	void _setViewProjectionMatrixBufferData() const;

	// Set light property buffer data
	void _setLightPropertyBufferData() const;

};

