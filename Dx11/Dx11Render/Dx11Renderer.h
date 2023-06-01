#pragma once


#include "../Render/Dx11Mesh.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Actor/Light/CrDirectionalLight.h"
#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


class Dx11Renderer
{
public:
	struct WorldMatrix
	{
		XMMATRIX worldMat;
	};

	struct ViewProjMatrix
	{
		XMMATRIX viewMat;
		XMMATRIX projMat;
	};

	struct LightProperty
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float    padding;
	};

private:
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11Buffer* WorldMatrixBuffer;
	ID3D11Buffer* ViewProjectionMatrixBuffer;
	ID3D11Buffer* LightPropertyBuffer;

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

	// Initialize world matrix buffer
	void _initializeWorldMatrixBuffer();

	// Initialize view projection matrix buffer
	void _initializeViewProjectionMatrixBuffer();

	// Initialize light property buffer
	void _initializeLightPropertyBuffer();

	// Set world matrix buffer data
	void _setWorldMatrixBufferData( const XMMATRIX& Matrix ) const;

	// Set view projection matrix buffer data
	void _setViewProjectionMatrixBufferData() const;

	// Set light property buffer data
	void _setLightPropertyBufferData() const;

};

