#pragma once


#include "Dx11Mesh.h"
#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


class Dx11Renderer
{

private:
	IDXGISwapChain*         SwapChain;
	ID3D11Device*           Device;
	ID3D11DeviceContext*    DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;

	Dx11Mesh Primitive;

public:
	// Constructor
	Dx11Renderer();

	// Clear
	void Clear();
	
	// Initialize
	void Initialize( HWND hWnd );

	// Render Frame
	void RenderFrame();

private:
	// Initialize RenderTargetView
	void _InitializeRenderTargetView();

	// Initialize Viewport
	void _InitializeViewport();
};

