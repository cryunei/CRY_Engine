#include "Dx11Renderer.h"
#include "../Core/Dx11Device.h"


//=================================================================================================
// @brief	Constructor
//=================================================================================================
Dx11Renderer::Dx11Renderer()
: RenderTargetView       ( nullptr )
, WorldMatrixBuffer      ( nullptr )
, ViewMatrixBuffer       ( nullptr )
, ProjectionMatrixBuffer ( nullptr )
{
}

//=================================================================================================
// @brief	Clear
//=================================================================================================
void Dx11Renderer::Clear()
{
	if ( RenderTargetView )RenderTargetView->Release();

	RenderTargetView = nullptr;
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Renderer::Initialize()
{
	_InitializeRenderTargetView();
	_InitializeViewport();

	Mesh.Initialize();
}

//=================================================================================================
// @brief	Render frame
//=================================================================================================
void Dx11Renderer::RenderFrame()
{
	float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };
	
	GetDx11DeviceContext()->ClearRenderTargetView( RenderTargetView, color );

	Mesh.Render();

	GetSwapChain()->Present( 0, 0 );
}

//=================================================================================================
// @brief	Initialize render target view
//=================================================================================================
void Dx11Renderer::_InitializeRenderTargetView()
{
	ID3D11Texture2D* texture = nullptr;

	GetSwapChain()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&texture );
	if ( !texture ) return;

	GetDx11Device()->CreateRenderTargetView( texture, nullptr, &RenderTargetView );
	GetDx11DeviceContext()->OMSetRenderTargets( 1, &RenderTargetView, nullptr );
	
	texture->Release();
}

//=================================================================================================
// @brief	Initialize viewport
//=================================================================================================
void Dx11Renderer::_InitializeViewport() const
{
	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( D3D11_VIEWPORT ) );

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	GetDx11DeviceContext()->RSSetViewports( 1, &viewport );
}

//=================================================================================================
// @brief	Initialize matrix buffer
//=================================================================================================
void Dx11Renderer::InitializeMatrixBuffer( ID3D11Buffer* Buffer ) const
{
	if ( Buffer )
	{
		Buffer->Release();
	}

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( XMMATRIX );
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	GetDx11Device()->CreateBuffer( &bd, nullptr, &Buffer );
}
