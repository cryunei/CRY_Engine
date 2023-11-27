#pragma once


#include "../Core/Dx11CoreTypes.h"
#include "../DxCoreInc.h"
#include <string>
#include <vector>


class Dx11ConstantBuffer;


//=====================================================================================================================
// @brief	EGlobalConstantBufferType
//=====================================================================================================================
enum class EGlobalConstantBufferType
{
    World,
    ViewProjection,
    Camera,
    LightLocation,
    RenderProperty,
    Light,
    Specular,    
    LightColor,
    Max
};

//=====================================================================================================================
// @brief	Dx11GlobalConstantBuffers
//=====================================================================================================================
class Dx11GlobalConstantBuffers
{
public:
    using GlobalConstantBufferList = std::vector< Dx11ConstantBuffer* >;

    struct BufferDescriptor
    {
        std::string           Name;
        size_t                Size;
        D3D11_USAGE           Usage;
        D3D11_CPU_ACCESS_FLAG CpuAccess;
        ERenderPipeLineStage  Stage;
        int                   RegisterIdx;

        BufferDescriptor( const std::string& InName, size_t InSize, D3D11_USAGE InUsage, D3D11_CPU_ACCESS_FLAG InCpuAccess, ERenderPipeLineStage InStage, int InRegisterIdx )
            : Name( InName ), Size( InSize ), Usage( InUsage ), CpuAccess( InCpuAccess ), Stage( InStage ), RegisterIdx( InRegisterIdx )
        {}
    };

    using BufferDescriptorList = std::vector< BufferDescriptor >;

private:
    GlobalConstantBufferList Buffers;
    BufferDescriptorList     BufferDescriptors;
    
public:
    // Constructor
    Dx11GlobalConstantBuffers();

    // Initialize
    void Initialize();

    // Initialize
    Dx11ConstantBuffer* GetBuffer( EGlobalConstantBufferType Type ) const { return Buffers[ (int)Type ]; }
};

//=====================================================================================================================
// @brief	Get directx 11 global constant buffers
//=====================================================================================================================
Dx11GlobalConstantBuffers* GetDx11GCB();
