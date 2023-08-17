#include "Dx11Renderer.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceManager.h"
#include "../Core/Dx11VertexShader.h"
#include "../GUI/GuiManager.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
Dx11Renderer::Dx11Renderer()
: RenderTargetView ( nullptr )
, ViewportWidth    ( 1920.f )
, ViewportHeight   ( 1080.f )
{
}

//=====================================================================================================================
// @brief	Clear
//=====================================================================================================================
void Dx11Renderer::Clear()
{
	if ( RenderTargetView )RenderTargetView->Release();

	RenderTargetView = nullptr;
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11Renderer::Initialize( int Width, int Height )
{
	_initializeRenderTargetView();
	_initializeViewport( Width, Height);
	_initializeConstantBuffers();	

	GetCamera()->SetLookAtDirection( Vector3( 0.f, 0.f, -1.f ) );
	GetCamera()->Transform.SetLocation( 0.f, 0.f, 25.f );

	GetGuiManager()->GetDevTestUI().BindCameraTransform( &GetCamera()->Transform );
}

//=====================================================================================================================
// @brief	Render frame
//=====================================================================================================================
void Dx11Renderer::RenderFrame()
{
	GetGuiManager()->PreRender();

	float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };
	
	GetDx11DeviceContext()->ClearRenderTargetView( RenderTargetView, color );

	_setViewProjectionMatrixBufferData();
	_setLightPropertyBufferData();

	RenderQueue.Render();

	GetGuiManager()->PostRender();

	GetSwapChain()->Present( 0, 0 );
}

//=====================================================================================================================
// @brief	Add mesh render element
//=====================================================================================================================
bool Dx11Renderer::AddMeshRenderElement( const Dx11Mesh* MeshPtr )
{
	if ( !MeshPtr ) return false;

	MeshPtr->IncreaseRenderCount();

	return RenderQueue.Add( MeshPtr, &WorldBuffer );
}

//=====================================================================================================================
// @brief	Sort render queue
//=====================================================================================================================
void Dx11Renderer::SortRenderQueue()
{
	RenderQueue.Sort();
}

//=====================================================================================================================
// @brief	Initialize render target view
//=====================================================================================================================
void Dx11Renderer::_initializeRenderTargetView()
{
	ID3D11Texture2D* texture = nullptr;

	GetSwapChain()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&texture );
	if ( !texture ) return;

	GetDx11Device()->CreateRenderTargetView( texture, nullptr, &RenderTargetView );
	GetDx11DeviceContext()->OMSetRenderTargets( 1, &RenderTargetView, nullptr );
}

//=====================================================================================================================
// @brief	Initialize viewport
//=====================================================================================================================
void Dx11Renderer::_initializeViewport( int Width, int Height )
{
	ViewportWidth  = Width;
	ViewportHeight = Height;

	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( D3D11_VIEWPORT ) );

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width  = ViewportWidth;
	viewport.Height = ViewportHeight;

	GetDx11DeviceContext()->RSSetViewports( 1, &viewport );
}

//=====================================================================================================================
// @brief	Initialize constant buffers
//=====================================================================================================================
void Dx11Renderer::_initializeConstantBuffers()
{
	WorldBuffer         . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	ViewProjBuffer      . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	CameraBuffer        . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightBuffer         . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	SpecularBuffer      . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightLocationBuffer . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightColorBuffer    . CreateBuffer( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );


	WorldBuffer        .SetRegister( ERenderPipeLineStage::VertexShader, 0 );
	ViewProjBuffer     .SetRegister( ERenderPipeLineStage::VertexShader, 1 );
	CameraBuffer       .SetRegister( ERenderPipeLineStage::VertexShader, 2 );
	LightLocationBuffer.SetRegister( ERenderPipeLineStage::VertexShader, 3 );
	LightBuffer        .SetRegister( ERenderPipeLineStage::PixelShader,  0 );
	SpecularBuffer     .SetRegister( ERenderPipeLineStage::PixelShader,  1 );
	LightColorBuffer   .SetRegister( ERenderPipeLineStage::PixelShader,  2 );
}

//=====================================================================================================================
// @brief	Set view projection matrix buffer data
//=====================================================================================================================
void Dx11Renderer::_setViewProjectionMatrixBufferData() const
{
	ViewProjMatrix mat( GetCamera()->GetViewMatrix().Transpose(), GetCamera()->GetProjectionMatrix( ViewportWidth, ViewportHeight ).Transpose() );

	ViewProjBuffer.Update( mat );

	CameraProperty prop( GetCamera()->Transform.GetLocation() );

	CameraBuffer.Update( prop );
}

//=====================================================================================================================
// @brief	Set light property buffer data
//=====================================================================================================================
void Dx11Renderer::_setLightPropertyBufferData() const
{
	LightProperty prop( Vector4( 0.f, 0.f, 0.15f, 1.f ), Vector4::One, Vector3( 1.0f, -1.0f, 1.0f ) );

	LightBuffer.Update( prop );

	SpecularProperty specularProp( Vector4( 0.5f, 0.5f, 0.5f, 1.f ), 32.0f );

	SpecularBuffer.Update( specularProp );

	Vector4 lightLocations[ MaxPointLightCount ] = { Vector4( -10.f, 10.f, -5.f, 1.f ), Vector4( -5.f, -8.f, -5.f, 1.f ), Vector4( 5.f, 8.f, -5.f, 1.f ), Vector4( 10.f, -8.f, -3.f, 1.f ) };
	Vector4 lightColors   [ MaxPointLightCount ] = { Vector4( 1.f, 1.f, 1.f, 1.f ), Vector4( 1.f, 0.f, 0.f, 1.f ), Vector4( 0.f, 1.f, 0.f, 1.f ), Vector4( 0.f, 0.f, 1.f, 1.f ) };

	PointLightLocation pointLightLocation( lightLocations );
	PointLightColor    pointLightColor   ( lightColors    );

	LightLocationBuffer.Update( pointLightLocation );
	LightColorBuffer   .Update( pointLightColor    );	
}
