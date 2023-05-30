#include "Dx11Renderer.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Core/Dx11Device.h"


//=================================================================================================
// @brief	Constructor
//=================================================================================================
Dx11Renderer::Dx11Renderer()
: RenderTargetView           ( nullptr )
, WorldMatrixBuffer          ( nullptr )
, ViewProjectionMatrixBuffer ( nullptr )
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
	_InitializeWorldMatrixBuffer();
	_InitializeViewProjectionMatrixBuffer();

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

	_SetViewProjectionMatrixBufferData();

	// foreach Mesh
	{
		_SetWorldMatrixBufferData( Mesh.GetTransform().GetWorldMatrix() ); 
		Mesh.Render();
	}

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
// @brief	Initialize world matrix buffer
//=================================================================================================
void Dx11Renderer::_InitializeWorldMatrixBuffer()
{
	if ( WorldMatrixBuffer )
	{
		WorldMatrixBuffer->Release();
	}

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( WorldMatrix );
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HRESULT hr = GetDx11Device()->CreateBuffer( &bd, nullptr, &WorldMatrixBuffer );
}

//=================================================================================================
// @brief	Initialize view projection matrix buffer
//=================================================================================================
void Dx11Renderer::_InitializeViewProjectionMatrixBuffer()
{
	if ( ViewProjectionMatrixBuffer )
	{
		ViewProjectionMatrixBuffer->Release();
	}

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( ViewProjMatrix );
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HRESULT hr = GetDx11Device()->CreateBuffer( &bd, nullptr, &ViewProjectionMatrixBuffer );
}

//=================================================================================================
// @brief	Set world matrix buffer data
//=================================================================================================
void Dx11Renderer::_SetWorldMatrixBufferData( const XMMATRIX& Matrix ) const
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
void Dx11Renderer::_SetViewProjectionMatrixBufferData() const
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