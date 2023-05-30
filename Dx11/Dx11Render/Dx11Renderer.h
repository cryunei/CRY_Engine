#pragma once


#include "../Render/Dx11Mesh.h"
#include "../Actor/Camera/CrCamera.h"
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

private:
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11Buffer* WorldMatrixBuffer;
	ID3D11Buffer* ViewProjectionMatrixBuffer;

	Dx11Mesh Mesh;
	CrCamera Camera;

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
	void _InitializeRenderTargetView();

	// Initialize viewport
	void _InitializeViewport() const;

	// Initialize world matrix buffer
	void _InitializeWorldMatrixBuffer();

	// Initialize view projection matrix buffer
	void _InitializeViewProjectionMatrixBuffer();

	// Initialize matrix buffer
	void _InitializeMatrixBuffer( ID3D11Buffer** Buffer ) const;

	// Set world matrix buffer data
	void _SetWorldMatrixBufferData( const XMMATRIX& Matrix ) const;

	// Set view projection matrix buffer data
	void _SetViewProjectionMatrixBufferData() const;

};

