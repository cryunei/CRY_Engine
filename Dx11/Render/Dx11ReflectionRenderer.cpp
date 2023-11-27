#include "Dx11ReflectionRenderer.h"
#include "Dx11GlobalConstantBuffers.h"
#include "Dx11Renderer.h"
#include "../Dx11.h"
#include "../Core/Dx11ObjectManager.h"


//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11ReflectionRenderer::Initialize()
{
    ReflectionBuffer = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "ReflectionBuffer" );
    ReflectionBuffer->CreateBuffer( sizeof( ReflectionMatrix ), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
    ReflectionBuffer->SetRegister( ERenderPipeLineStage::VertexShader, 0 );

    ReflectionPropertyBuffer = GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, "ReflectionPropertyBuffer" );
    ReflectionPropertyBuffer->CreateBuffer( sizeof( ReflectionProperty ), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE );
    ReflectionPropertyBuffer->SetRegister( ERenderPipeLineStage::PixelShader, 0 );
}

//=====================================================================================================================
// @brief	Add reflector
//=====================================================================================================================
void Dx11ReflectionRenderer::AddReflector( const std::string& Name, const DxTransform& Transform, unsigned int Width, unsigned int Height, float Intensity )
{
    Reflectors.emplace_back( Name, Transform, Width, Height, Intensity );

    Reflector& reflector = Reflectors.back();
    reflector.RenderQueue.InitializeRenderTarget( Name );
    reflector.RenderQueue.GetRenderTarget()->Initialize( Name + "_Texture", Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM );
    reflector.RenderQueue.SetCamera( &reflector.Camera );
}

//=====================================================================================================================
// @brief	Add mesh render element
//=====================================================================================================================
void Dx11ReflectionRenderer::AddMeshRenderElement( const CrMeshActor& MeshActor )
{
    for ( auto& reflector : Reflectors )
    {
        reflector.RenderQueue.Add( MeshActor );
    }
}

//=====================================================================================================================
// @brief	SortRenderQueue
//=====================================================================================================================
void Dx11ReflectionRenderer::SortRenderQueue()
{
    for ( auto& reflector : Reflectors )
    {
        reflector.RenderQueue.Sort();
    }
}

//=====================================================================================================================
// @brief	Render frame
//=====================================================================================================================
void Dx11ReflectionRenderer::RenderFrame()
{     
    G_Dx11Renderer.EnableBlendState();
    
    for ( auto& reflector : Reflectors )
    {
        const Plane& reflectionPlane = _GetReflectionPlane( reflector.Transform );
        const Vector3 normal = Vector3( reflectionPlane.x, reflectionPlane.y, reflectionPlane.z ); 

        const Vector3& reflectLocation = -normal * reflectionPlane.w * 2.f;

        CrCamera& camera = reflector.Camera;
        camera.GetTransform()->SetLocation( reflectLocation.x, reflectLocation.y, reflectLocation.z );
        camera.SetLookAtDirection( normal );
    
        reflector.RenderQueue.Render();
    }

    G_Dx11Renderer.DisableBlendState();
}

//=====================================================================================================================
// @brief	Set reflection buffer
//=====================================================================================================================
void Dx11ReflectionRenderer::SetReflectionBuffer( const std::string& ReflectorName )
{
    auto find = std::find_if( Reflectors.begin(), Reflectors.end(), [ &ReflectorName ]( const Reflector& reflector )
    {
        return reflector.Name == ReflectorName;
    } );

    if ( find == Reflectors.end() ) return;

    ReflectionBuffer        ->Update< ReflectionMatrix   >( ReflectionMatrix( find->Camera.GetViewMatrix().Transpose() ) );
    ReflectionPropertyBuffer->Update< ReflectionProperty >( find->Intensity );
}

//=====================================================================================================================
// @brief	Get reflection plane
//=====================================================================================================================
Plane Dx11ReflectionRenderer::_GetReflectionPlane( const DxTransform& Transform ) const
{
    const Matrix& worldMatrix = Transform.GetWorldMatrix();

    // 31, 32, 33 element means axis-z and it is normal vector 
    const Vector3& normal = Vector3( worldMatrix._31, worldMatrix._32, worldMatrix._33 );  

    // 41, 42, 43 element means location form origin
    float d = -normal.Dot( Vector3( worldMatrix._41, worldMatrix._42, worldMatrix._43 ) );

    // plane equation
    return Plane( normal.x, normal.y, normal.z, d );
}
