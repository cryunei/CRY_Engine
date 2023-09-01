#include "Dx11Renderer.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceManager.h"
#include "../Core/Dx11VertexShader.h"
#include "../GUI/GuiManager.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
Dx11Renderer::Dx11Renderer()
: ViewportWidth  ( 1920.f )
, ViewportHeight ( 1080.f )
{
}

//=====================================================================================================================
// @brief	Clear
//=====================================================================================================================
void Dx11Renderer::Clear()
{
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11Renderer::Initialize( int Width, int Height )
{
	_initializeConstantBuffers();	

	GetCamera()->SetLookAtDirection( Vector3( 0.f, 0.f, -1.f ) );
	GetCamera()->Transform.SetLocation( 0.f, 0.f, 40.f );

	Camera_RT.SetLookAtDirection( Vector3( 0.f, 0.f, -1.f ) );
	Camera_RT.Transform.SetLocation( 0.f, 0.f, 15.f );

	GetGuiManager()->GetDevTestUI().BindCameraTransform( &GetCamera()->Transform );

	SetLightDirection( Vector3( 1.f, -1.f, 1.f ) );

	RenderQueueScreen.Initialize( Width, Height );
	RenderQueueScreen.SetCamera( GetCamera() );
}

//=====================================================================================================================
// @brief	Add render target
//=====================================================================================================================
void Dx11Renderer::AddRenderTarget( const std::string& RenderTargetName, int Width, int Height, DXGI_FORMAT Format )
{
	auto ret = RenderQueues.insert( std::make_pair( RenderTargetName, Dx11RenderQueue() ) );
	if ( ret.second )
	{
		Dx11RenderQueue& renderQ = ret.first->second;
		renderQ.GetRenderTarget()->Initialize( RenderTargetName + "_Texture", Width, Height, Format );
		renderQ.SetCamera( &Camera_RT );
	}
}

//=====================================================================================================================
// @brief	Render frame
//=====================================================================================================================
void Dx11Renderer::RenderFrame()
{
	GetGuiManager()->PreRender();

	_setLightPropertyBufferData();

	for ( auto itr = RenderQueues.begin(); itr != RenderQueues.end(); ++itr )
	{
		Dx11RenderQueue& renderQ = itr->second;
		_setViewProjectionMatrixBufferData( renderQ.GetCamera(), renderQ.GetViewportWidth(), renderQ.GetViewportHeight() );
		renderQ.Render();
	}

	_setViewProjectionMatrixBufferData( RenderQueueScreen.GetCamera(), RenderQueueScreen.GetViewportWidth(), RenderQueueScreen.GetViewportHeight() );
	RenderQueueScreen.Render();

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

	return RenderQueueScreen.Add( MeshPtr, &WorldBuffer );
}

//=====================================================================================================================
// @brief	Add mesh render element
//=====================================================================================================================
bool Dx11Renderer::AddMeshRenderElement( const Dx11Mesh* MeshPtr, const std::string& RenderTargetName )
{
	if ( !MeshPtr ) return false;

	if ( Dx11RenderQueue* renderQ = GetRenderQueue( RenderTargetName ) )
	{
		return renderQ->Add( MeshPtr, &WorldBuffer );
	}

	return false;
}

//=====================================================================================================================
// @brief	Sort render queue
//=====================================================================================================================
void Dx11Renderer::SortRenderQueue()
{
	for ( auto itr = RenderQueues.begin(); itr != RenderQueues.end(); ++itr )
	{
		itr->second.Sort();
	}

	RenderQueueScreen.Sort();
}

//=====================================================================================================================
// @brief	SetLightDirection
//=====================================================================================================================
void Dx11Renderer::SetLightDirection( const Vector3& Direction )
{
	Light.SetDirection( Direction );
	LightProperty prop( Light.GetColor(), Vector4::One, Light.GetDirection() );

	LightBuffer.Update( prop );
}

//=====================================================================================================================
// @brief	RenderTargetName
//=====================================================================================================================
Dx11RenderQueue* Dx11Renderer::GetRenderQueue( const std::string& RenderTargetName )
{
	auto itr = RenderQueues.find( RenderTargetName );
	if ( itr == RenderQueues.end() ) return nullptr;

	return &itr->second;
}

//=====================================================================================================================
// @brief	Dx11RenderTarget* GetRenderTarget( const std::string& RenderTargetName );
//=====================================================================================================================
Dx11RenderTarget* Dx11Renderer::GetRenderTarget( const std::string& RenderTargetName )
{
	if ( Dx11RenderQueue* renerQ = GetRenderQueue( RenderTargetName ) )
	{
		return renerQ->GetRenderTarget();
	}

	return nullptr;
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
void Dx11Renderer::_setViewProjectionMatrixBufferData( const CrCamera* Camera, unsigned int InViewportWidth, unsigned int InViewportHeight ) const
{
	if ( !Camera ) return;

	ViewProjMatrix mat( Camera->GetViewMatrix().Transpose(), Camera->GetProjectionMatrix( InViewportWidth, InViewportHeight ).Transpose() );

	ViewProjBuffer.Update( mat );

	CameraProperty prop( Camera->Transform.GetLocation() );

	CameraBuffer.Update( prop );
}

//=====================================================================================================================
// @brief	Set light property buffer data
//=====================================================================================================================
void Dx11Renderer::_setLightPropertyBufferData() const
{
	SpecularProperty specularProp( Vector4( 0.5f, 0.5f, 0.5f, 1.f ), 32.0f );

	SpecularBuffer.Update( specularProp );

	Vector4 lightLocations[ MaxPointLightCount ] = { Vector4( -10.f, 10.f, -5.f, 1.f ), Vector4( -5.f, -8.f, -5.f, 1.f ), Vector4( 5.f, 8.f, -5.f, 1.f ), Vector4( 10.f, -8.f, -3.f, 1.f ) };
	Vector4 lightColors   [ MaxPointLightCount ] = { Vector4( 1.f, 1.f, 1.f, 1.f ), Vector4( 1.f, 0.f, 0.f, 1.f ), Vector4( 0.f, 1.f, 0.f, 1.f ), Vector4( 0.f, 0.f, 1.f, 1.f ) };

	PointLightLocation pointLightLocation( lightLocations );
	PointLightColor    pointLightColor   ( lightColors    );

	LightLocationBuffer.Update( pointLightLocation );
	LightColorBuffer   .Update( pointLightColor    );	
}
