#include "Dx11Renderer.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Core/Dx11Device.h"
#include "../GUI/GuiManager.h"


//=================================================================================================
// @brief	Constructor
//=================================================================================================
Dx11Renderer::Dx11Renderer()
: RenderTargetView ( nullptr )
, ViewportWidth    ( 800.f )
, ViewportHeight   ( 600.f )
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
	_initializeRenderTargetView();
	_initializeViewport();
	_initializeConstantBuffers();	

	Mesh.Initialize();

	GetCamera()->SetLookAtDirection( Vector3( 0.f, 0.f, -1.f ) );
	GetCamera()->Transform.SetLocation( 0.f, 0.f, 25.f );
}

//=================================================================================================
// @brief	Render frame
//=================================================================================================
void Dx11Renderer::RenderFrame()
{
	GetGuiManager()->PreRender();

	float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };
	
	GetDx11DeviceContext()->ClearRenderTargetView( RenderTargetView, color );

	_setViewProjectionMatrixBufferData();
	_setLightPropertyBufferData();

	// foreach Mesh
	{
		Mesh.GetTransform().SetLocationX( 0.f );
		_setWorldMatrixBufferData( Mesh.GetTransform().GetWorldMatrix() ); 
		Mesh.Render();
	}

	GetGuiManager()->PostRender();

	GetSwapChain()->Present( 0, 0 );
}

//=================================================================================================
// @brief	Initialize render target view
//=================================================================================================
void Dx11Renderer::_initializeRenderTargetView()
{
	ID3D11Texture2D* texture = nullptr;

	GetSwapChain()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&texture );
	if ( !texture ) return;

	GetDx11Device()->CreateRenderTargetView( texture, nullptr, &RenderTargetView );
	GetDx11DeviceContext()->OMSetRenderTargets( 1, &RenderTargetView, nullptr );
}

//=================================================================================================
// @brief	Initialize viewport
//=================================================================================================
void Dx11Renderer::_initializeViewport() const
{
	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( D3D11_VIEWPORT ) );

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = ViewportWidth;
	viewport.Height = ViewportHeight;

	GetDx11DeviceContext()->RSSetViewports( 1, &viewport );
}

//=================================================================================================
// @brief	Initialize constant buffers
//=================================================================================================
void Dx11Renderer::_initializeConstantBuffers()
{
	WorldMatrixBuffer         .CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	ViewProjectionMatrixBuffer.CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightPropertyBuffer       .CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );

	WorldMatrixBuffer         .SetVS( 0 );
	ViewProjectionMatrixBuffer.SetVS( 1 );
	LightPropertyBuffer       .SetPS( 2 );
}

//=================================================================================================
// @brief	Set world matrix buffer data
//=================================================================================================
void Dx11Renderer::_setWorldMatrixBufferData( const XMMATRIX& Matrix ) const
{
	WorldMatrix mat{};
	mat.worldMat = XMMatrixTranspose( Matrix );

	WorldMatrixBuffer.Update( mat );
}

//=================================================================================================
// @brief	Set view projection matrix buffer data
//=================================================================================================
void Dx11Renderer::_setViewProjectionMatrixBufferData() const
{
	ViewProjMatrix mat{};
	mat.viewMat = GetCamera()->GetViewMatrix().Transpose();
	mat.projMat = GetCamera()->GetProjectionMatrix( ViewportWidth, ViewportHeight ).Transpose();

	ViewProjectionMatrixBuffer.Update( mat );
}

//=================================================================================================
// @brief	Set light property buffer data
//=================================================================================================
void Dx11Renderer::_setLightPropertyBufferData() const
{
	LightProperty prop{};	
	prop.diffuseColor   = Vector4::One;
	prop.lightDirection = Vector3( 1.0f, -1.0f, 1.0f );
	prop.padding        = 0.f;

	LightPropertyBuffer.Update( prop );
}
