#include "Dx11Renderer.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ObjectManager.h"
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

	RenderQueueScreen.InitializeRenderTarget( "Screen" );
	RenderQueueScreen.SetCamera( GetCamera() );

	BlendedRenderQueueScreen.InitializeRenderTarget( "Screen" );
	BlendedRenderQueueScreen.SetCamera( GetCamera() );

	RenderQueueScreen.GetRenderTarget()->Initialize( Width, Height );

	ChangeBlendState( D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD );
}

//=====================================================================================================================
// @brief	Add render target
//=====================================================================================================================
void Dx11Renderer::AddRenderTarget( const std::string& RenderTargetName, int Width, int Height, DXGI_FORMAT Format )
{
	auto ret = RenderToTextureQueues.insert( std::make_pair( RenderTargetName, Dx11RenderQueue() ) );
	if ( ret.second )
	{
		Dx11RenderQueue& renderQ = ret.first->second;
		renderQ.InitializeRenderTarget( RenderTargetName );
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

	float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f }; 
	const auto& renderTargets = GetDx11ObjectManager()->GetMap( EDx11ResourceType::RenderTarget );
	for ( auto itr = renderTargets.begin(); itr != renderTargets.end(); ++itr )
	{
		const Dx11RenderTarget* renderTarget = (Dx11RenderTarget*)( itr->second );
		if ( !renderTarget ) continue;

		renderTarget->Clear( clearColor );
	}

	_setLightPropertyBufferData();

	for ( auto itr = RenderToTextureQueues.begin(); itr != RenderToTextureQueues.end(); ++itr )
	{
		Dx11RenderQueue& renderQ = itr->second;
		_setViewProjectionMatrixBufferData( renderQ.GetCamera(), renderQ.GetViewportWidth(), renderQ.GetViewportHeight() );
		renderQ.Render();
	}

	_setViewProjectionMatrixBufferData( RenderQueueScreen.GetCamera(), RenderQueueScreen.GetViewportWidth(), RenderQueueScreen.GetViewportHeight() );

	DisableBlendState();
	RenderQueueScreen.Render();

	EnableBlendState();
	BlendedRenderQueueScreen.Render();

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

	if ( MeshPtr->GetOpacity() < 1.f )
	{
		return BlendedRenderQueueScreen.Add( MeshPtr, WorldBuffer, RenderPropertyBuffer );
	}

	return RenderQueueScreen.Add( MeshPtr, WorldBuffer, RenderPropertyBuffer );
}

//=====================================================================================================================
// @brief	Add mesh render element
//=====================================================================================================================
bool Dx11Renderer::AddMeshRenderElement( const Dx11Mesh* MeshPtr, const std::string& RenderTargetName )
{
	if ( !MeshPtr ) return false;

	if ( RenderTargetName == "" )
	{
		return AddMeshRenderElement( MeshPtr );
	}

	if ( Dx11RenderQueue* renderQ = GetRenderToTextureQueue( RenderTargetName ) )
	{
		return renderQ->Add( MeshPtr, WorldBuffer, RenderPropertyBuffer );
	}

	return false;
}

//=====================================================================================================================
// @brief	Sort render queue
//=====================================================================================================================
void Dx11Renderer::SortRenderQueue()
{
	for ( auto itr = RenderToTextureQueues.begin(); itr != RenderToTextureQueues.end(); ++itr )
	{
		itr->second.Sort();
	}

	RenderQueueScreen.Sort();
	BlendedRenderQueueScreen.Sort();
}

//=====================================================================================================================
// @brief	Change blend state
//=====================================================================================================================
void Dx11Renderer::ChangeBlendState( D3D11_BLEND SrcBlend, D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcBlendAlpha, D3D11_BLEND DestBlendAlpha, D3D11_BLEND_OP BlendOpAlpha )
{
	SAFE_RELEASE_COMPTR( BlendStateComPtr );

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );
	blendDesc.RenderTarget[ 0 ].BlendEnable = TRUE;
	blendDesc.RenderTarget[ 0 ].SrcBlend = SrcBlend;
	blendDesc.RenderTarget[ 0 ].DestBlend = DestBlend;
	blendDesc.RenderTarget[ 0 ].BlendOp = BlendOp;
	blendDesc.RenderTarget[ 0 ].SrcBlendAlpha = SrcBlendAlpha;
	blendDesc.RenderTarget[ 0 ].DestBlendAlpha = DestBlendAlpha;
	blendDesc.RenderTarget[ 0 ].BlendOpAlpha = BlendOpAlpha;
	blendDesc.RenderTarget[ 0 ].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GetDx11Device()->CreateBlendState( &blendDesc, &BlendStateComPtr );
}

//=====================================================================================================================
// @brief	Enable blend state
//=====================================================================================================================
void Dx11Renderer::EnableBlendState() const
{
	GetDx11DeviceContext()->OMSetBlendState( BlendStateComPtr.Get(), nullptr, 0xffffffff );
}

//=====================================================================================================================
// @brief	Disable blend state
//=====================================================================================================================
void Dx11Renderer::DisableBlendState() const
{
	GetDx11DeviceContext()->OMSetBlendState( nullptr, nullptr, 0xffffffff );
}

//=====================================================================================================================
// @brief	SetLightDirection
//=====================================================================================================================
void Dx11Renderer::SetLightDirection( const Vector3& Direction )
{
	Light.SetDirection( Direction );
	LightProperty prop( Light.GetColor(), Vector4::One, Light.GetDirection() );

	LightBuffer->Update< LightProperty >( prop );
}

//=====================================================================================================================
// @brief	RenderTargetName
//=====================================================================================================================
Dx11RenderQueue* Dx11Renderer::GetRenderToTextureQueue( const std::string& RenderTargetName )
{
	auto itr = RenderToTextureQueues.find( RenderTargetName );
	if ( itr == RenderToTextureQueues.end() ) return nullptr;

	return &itr->second;
}

//=====================================================================================================================
// @brief	Dx11RenderTarget* GetRenderTarget( const std::string& RenderTargetName );
//=====================================================================================================================
Dx11RenderTarget* Dx11Renderer::GetRenderTarget( const std::string& RenderTargetName )
{
	if ( Dx11RenderQueue* renerQ = GetRenderToTextureQueue( RenderTargetName ) )
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
	WorldBuffer          = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "WorldBuffer" );
	ViewProjBuffer       = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "ViewProjBuffer" );
	CameraBuffer         = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "CameraBuffer" );
	RenderPropertyBuffer = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "RenderPropertyBuffer" );
	LightBuffer          = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "LightBuffer" );
	SpecularBuffer       = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "SpecularBuffer" );
	LightLocationBuffer  = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "LightLocationBuffer" );
	LightColorBuffer     = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "LightColorBuffer" );


	WorldBuffer         ->CreateBuffer< WorldMatrix        >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	ViewProjBuffer      ->CreateBuffer< ViewProjMatrix     >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	CameraBuffer        ->CreateBuffer< CameraProperty     >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	RenderPropertyBuffer->CreateBuffer< RenderProperty     >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightBuffer         ->CreateBuffer< LightProperty      >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	SpecularBuffer      ->CreateBuffer< SpecularProperty   >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightLocationBuffer ->CreateBuffer< PointLightLocation >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
	LightColorBuffer    ->CreateBuffer< PointLightColor    >( D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );

	WorldBuffer         ->SetRegister( ERenderPipeLineStage::VertexShader, 0 );
	ViewProjBuffer      ->SetRegister( ERenderPipeLineStage::VertexShader, 1 );
	CameraBuffer        ->SetRegister( ERenderPipeLineStage::VertexShader, 2 );	
	LightLocationBuffer ->SetRegister( ERenderPipeLineStage::VertexShader, 3 );
	RenderPropertyBuffer->SetRegister( ERenderPipeLineStage::PixelShader,  0 );
	LightBuffer         ->SetRegister( ERenderPipeLineStage::PixelShader,  10 );
	SpecularBuffer      ->SetRegister( ERenderPipeLineStage::PixelShader,  11 );
	LightColorBuffer    ->SetRegister( ERenderPipeLineStage::PixelShader,  12 );
}

//=====================================================================================================================
// @brief	Set view projection matrix buffer data
//=====================================================================================================================
void Dx11Renderer::_setViewProjectionMatrixBufferData( const CrCamera* Camera, unsigned int InViewportWidth, unsigned int InViewportHeight ) const
{
	if ( !Camera ) return;

	ViewProjBuffer->Update< ViewProjMatrix >( ViewProjMatrix( Camera->GetViewMatrix().Transpose(), Camera->GetProjectionMatrix( (float)( InViewportWidth ), (float)( InViewportHeight ) ).Transpose() ) );

	CameraBuffer->Update< CameraProperty >( CameraProperty( Camera->Transform.GetLocation() ) );
}

//=====================================================================================================================
// @brief	Set light property buffer data
//=====================================================================================================================
void Dx11Renderer::_setLightPropertyBufferData() const
{
	SpecularProperty specularProp( Vector4( 0.5f, 0.5f, 0.5f, 1.f ), 32.0f );

	SpecularBuffer->Update< SpecularProperty >( specularProp );

	Vector4 lightLocations[ MaxPointLightCount ] = { Vector4( -10.f, 10.f, -5.f, 1.f ), Vector4( -5.f, -8.f, -5.f, 1.f ), Vector4( 5.f, 8.f, -5.f, 1.f ), Vector4( 10.f, -8.f, -3.f, 1.f ) };
	Vector4 lightColors   [ MaxPointLightCount ] = { Vector4( 1.f, 1.f, 1.f, 1.f ), Vector4( 1.f, 0.f, 0.f, 1.f ), Vector4( 0.f, 1.f, 0.f, 1.f ), Vector4( 0.f, 0.f, 1.f, 1.f ) };

	PointLightLocation pointLightLocation( lightLocations );
	PointLightColor	   pointLightColor   ( lightColors    );

	LightLocationBuffer->Update< PointLightLocation >( lightLocations );
	LightColorBuffer   ->Update< PointLightColor    >( lightColors    );	
}
