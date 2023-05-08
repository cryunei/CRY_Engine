#include "Dx11Renderer.h"

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Dx11Renderer::Dx11Renderer()
: SwapChain        ( nullptr )
, Device           ( nullptr )
, DeviceContext    ( nullptr )
, RenderTargetView ( nullptr )
{
}

//------------------------------------------------------------------------------
// Clear
//------------------------------------------------------------------------------
void Dx11Renderer::Clear()
{
	if ( SwapChain ) SwapChain->Release();
	if ( Device ) Device->Release();
	if ( DeviceContext ) DeviceContext->Release();
	if ( RenderTargetView )RenderTargetView->Release();

	SwapChain = nullptr;
	Device = nullptr;
	DeviceContext = nullptr;
	RenderTargetView = nullptr;
}

//------------------------------------------------------------------------------
// Initialize
//------------------------------------------------------------------------------
void Dx11Renderer::Initialize( HWND hWnd )
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory( &scd, sizeof( DXGI_SWAP_CHAIN_DESC ) );

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = true;

	D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &SwapChain, &Device, nullptr, &DeviceContext);

	_InitializeRenderTargetView();
	_InitializeViewport();

	Primitive.Initialize( Device, DeviceContext );
}

//------------------------------------------------------------------------------
// RenderFrame
//------------------------------------------------------------------------------
void Dx11Renderer::RenderFrame()
{
	if ( !DeviceContext ) return;
	if ( !SwapChain ) return;
	
	float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };
	
	DeviceContext->ClearRenderTargetView( RenderTargetView, color );

	Primitive.Render( DeviceContext );

	SwapChain->Present( 0, 0 );
}

//------------------------------------------------------------------------------
// _InitializeRenderTargetView
//------------------------------------------------------------------------------
void Dx11Renderer::_InitializeRenderTargetView()
{
	if ( !SwapChain ) return;
	if ( !Device ) return;
	if ( !DeviceContext ) return;
	
	ID3D11Texture2D* texture = nullptr;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&texture );
	if ( !texture ) return;

	Device->CreateRenderTargetView( texture, nullptr, &RenderTargetView );
	texture->Release();

	DeviceContext->OMSetRenderTargets( 1, &RenderTargetView, nullptr );
}

//------------------------------------------------------------------------------
// _InitializeViewport
//------------------------------------------------------------------------------
void Dx11Renderer::_InitializeViewport()
{
	if ( !DeviceContext ) return;
	
	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( D3D11_VIEWPORT ) );

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	DeviceContext->RSSetViewports( 1, &viewport );
}