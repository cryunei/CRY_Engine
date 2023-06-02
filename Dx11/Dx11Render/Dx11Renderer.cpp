#include "Dx11Renderer.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"

//=================================================================================================
// @brief	Constructor
//=================================================================================================
Dx11Renderer::Dx11Renderer()
: RenderTargetView           ( nullptr )
, WorldMatrixBuffer          ( nullptr )
, ViewProjectionMatrixBuffer ( nullptr )
, LightPropertyBuffer		 ( nullptr )
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
	GetCamera()->Transform.SetLocation( 0.f, 0.f, 5.f );
}

//=================================================================================================
// @brief	Render frame
//=================================================================================================
void Dx11Renderer::RenderFrame()
{
	float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };
	
	GetDx11DeviceContext()->ClearRenderTargetView( RenderTargetView, color );

	_setViewProjectionMatrixBufferData();
	_setLightPropertyBufferData();

	// foreach Mesh
	{
		_setWorldMatrixBufferData( Mesh.GetTransform().GetWorldMatrix() ); 
		Mesh.Render();
	}

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
	
	texture->Release();
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
	viewport.Width = 800;
	viewport.Height = 600;

	GetDx11DeviceContext()->RSSetViewports( 1, &viewport );
}

//=================================================================================================
// @brief	Initialize constant buffers
//=================================================================================================
void Dx11Renderer::_initializeConstantBuffers()
{
	Dx11ResourceFactory::CreateConstantBuffer( &WorldMatrixBuffer, sizeof( WorldMatrix ) );
	Dx11ResourceFactory::CreateConstantBuffer( &ViewProjectionMatrixBuffer, sizeof( ViewProjMatrix ) );
	Dx11ResourceFactory::CreateConstantBuffer( &LightPropertyBuffer, sizeof( LightProperty ) );
}

//=================================================================================================
// @brief	Set world matrix buffer data
//=================================================================================================
void Dx11Renderer::_setWorldMatrixBufferData( const XMMATRIX& Matrix ) const
{
	if ( !WorldMatrixBuffer ) return;

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	WorldMatrix* dataPtr = nullptr;

	GetDx11DeviceContext()->Map( WorldMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
	{
		dataPtr = ( WorldMatrix* )mappedResource.pData;

		dataPtr->worldMat = XMMatrixTranspose( Matrix );
	}
	GetDx11DeviceContext()->Unmap( WorldMatrixBuffer, 0 );

	GetDx11DeviceContext()->VSSetConstantBuffers( 0, 1, &WorldMatrixBuffer );
}

//=================================================================================================
// @brief	Set view projection matrix buffer data
//=================================================================================================
void Dx11Renderer::_setViewProjectionMatrixBufferData() const
{
	if ( !ViewProjectionMatrixBuffer ) return;

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	ViewProjMatrix* dataPtr = nullptr;

	GetDx11DeviceContext()->Map( ViewProjectionMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
	{
		dataPtr = ( ViewProjMatrix* )mappedResource.pData;
	
		dataPtr->viewMat = GetCamera()->GetViewMatrix().Transpose();
		dataPtr->projMat = GetCamera()->GetProjectionMatrix().Transpose();

	}
	GetDx11DeviceContext()->Unmap( ViewProjectionMatrixBuffer, 0 );

	GetDx11DeviceContext()->VSSetConstantBuffers( 1, 1, &ViewProjectionMatrixBuffer );
}

//=================================================================================================
// @brief	Set light property buffer data
//=================================================================================================
void Dx11Renderer::_setLightPropertyBufferData() const
{
	if ( !LightPropertyBuffer ) return;

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	LightProperty* dataPtr = nullptr;

	GetDx11DeviceContext()->Map( LightPropertyBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
	{
		dataPtr = ( LightProperty* )mappedResource.pData;

		dataPtr->diffuseColor   = Vector4::One;
		dataPtr->lightDirection = Vector3( 0.0f, 0.0f, -1.0f );
		dataPtr->padding        = 0.f;
	}
	GetDx11DeviceContext()->Unmap( LightPropertyBuffer, 0 );

	GetDx11DeviceContext()->PSSetConstantBuffers( 2, 1, &LightPropertyBuffer );
}
