#include "Dx11GlobalConstantBuffers.h"
#include "Dx11ConstantBufferStructure.h"
#include "../Core/Dx11ObjectManager.h"


Dx11GlobalConstantBuffers G_Dx11GlobalConstantBuffers;
Dx11GlobalConstantBuffers* GetDx11GCB() { return &G_Dx11GlobalConstantBuffers; }


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
Dx11GlobalConstantBuffers::Dx11GlobalConstantBuffers()
{
    BufferDescriptors =
    {
        BufferDescriptor( "WorldBuffer",          sizeof( WorldMatrix ),        D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::VertexShader, 10 ),
        BufferDescriptor( "ViewProjectionBuffer", sizeof( ViewProjMatrix ),     D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::VertexShader, 11 ),
        BufferDescriptor( "CameraBuffer",         sizeof( CameraProperty ),     D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::VertexShader, 12 ),
        BufferDescriptor( "LightLocationBuffer",  sizeof( PointLightLocation ), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::VertexShader, 13 ),
        BufferDescriptor( "RenderPropertyBuffer", sizeof( RenderProperty ),     D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::PixelShader,  10 ),
        BufferDescriptor( "LightBuffer",          sizeof( LightProperty ),      D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::PixelShader,  11 ),
        BufferDescriptor( "SpecularBuffer",       sizeof( SpecularProperty ),   D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::PixelShader,  12 ),        
        BufferDescriptor( "LightColorBuffer",     sizeof( PointLightColor ),    D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, ERenderPipeLineStage::PixelShader,  13 ),
    };
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11GlobalConstantBuffers::Initialize()
{
    Buffers.reserve( (int)( EGlobalConstantBufferType::Max ) );

    for ( int i = 0; i < (int)( EGlobalConstantBufferType::Max ); ++i )
    {
        Buffers.push_back( GetDx11ObjectManager()->Get< Dx11ConstantBuffer >( EDx11ResourceType::ConstantBuffer, BufferDescriptors[ i ].Name ) );
        Buffers.back()->CreateBuffer( BufferDescriptors[ i ].Size, BufferDescriptors[ i ].Usage, BufferDescriptors[ i ].CpuAccess );
        Buffers.back()->SetRegister( BufferDescriptors[ i ].Stage, BufferDescriptors[ i ].RegisterIdx );
    }
}
