#pragma once


#include "../Render/Dx11Mesh.h"
#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


class Dx11Renderer
{

private:
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11Buffer*           WorldMatrixBuffer;
	ID3D11Buffer*           ViewMatrixBuffer;
	ID3D11Buffer*           ProjectionMatrixBuffer;

	Dx11Mesh Mesh;

public:
	// Constructor
	Dx11Renderer();

	// Clear
	void Clear();
	
	// Initialize
	void Initialize();

	// Render frame
	void RenderFrame();

private:
	// Initialize render target view
	void _InitializeRenderTargetView();

	// Initialize viewport
	void _InitializeViewport() const;

	// Initialize matrix buffer
	void InitializeMatrixBuffer( ID3D11Buffer* Buffer ) const;
};

