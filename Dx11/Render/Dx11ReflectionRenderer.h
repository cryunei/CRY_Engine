#pragma once


#include "Dx11Mesh.h"
#include "Dx11RenderQueue.h"
#include "../Actor/Camera/CrCamera.h"
#include <map>

class DxTransform;
class Dx11ConstantBuffer;


//=====================================================================================================================
// @brief	Dx11ReflectionRenderer
//=====================================================================================================================
class Dx11ReflectionRenderer
{
private:
    //=================================================================================================================
    // Dx constant buffers
    //=================================================================================================================
    struct ReflectionMatrix
    {
        XMMATRIX reflectionMat;

        // Construct
        ReflectionMatrix( const XMMATRIX& InMat ) : reflectionMat( InMat ) {}
    };

    struct ReflectionProperty
    {
        float    intensity;
        XMFLOAT3 padding;

        // Construct
        ReflectionProperty( float InIntensity ) : intensity( InIntensity ), padding( 1.0f, 1.0f, 1.0f ) {}
    };

    //=================================================================================================================
    // Reflector
    //=================================================================================================================
    struct Reflector
    {
        std::string     Name;
        DxTransform     Transform;        
        unsigned int    Width;
        unsigned int    Height;
        float           Intensity;
        CrCamera        Camera;
        Dx11RenderQueue RenderQueue;

        // Construct
        Reflector( const std::string& InName, const DxTransform& InTransform, unsigned int InWidth, unsigned int InHeight, float InIntensity )
            : Name( InName ), Transform( InTransform ), Width( InWidth ), Height( InHeight ), Intensity( InIntensity ) {}
    };

    using ReflectorList = std::vector< Reflector >;

private:
    Dx11ConstantBuffer*               ReflectionBuffer         = nullptr;
    Dx11ConstantBuffer*               ReflectionPropertyBuffer = nullptr;    
    ReflectorList                     Reflectors;
    std::map< std::string, CrCamera > Cameras;

public:
    // Initialize
    void Initialize();

    // Add reflector
    void AddReflector( const std::string& Name, const DxTransform& Transform, unsigned int Width, unsigned int Height, float Intensity );

    // Add mesh render element
    void AddMeshRenderElement( const CrMeshActor& MeshActor );

    // Sort render queue
    void SortRenderQueue();

    // Render frame
    void RenderFrame();

    // Set reflection buffer
    void SetReflectionBuffer( const std::string& ReflectorName );

private:
    // Get reflection plane
    Plane _GetReflectionPlane( const DxTransform& Transform ) const;    
};
