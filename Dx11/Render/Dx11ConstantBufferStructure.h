#pragma once


#include "../Core/Dx11ConstantBuffer.h"


static constexpr int MaxPointLightCount = 4;


//=====================================================================================================================
// @brief	WorldMatrix
//=====================================================================================================================
struct WorldMatrix
{
    XMMATRIX worldMat;

    // Construct
    WorldMatrix( const XMMATRIX& InWorldMat ) : worldMat( InWorldMat ) {}
};
using WorldMatrixBuffer = Dx11ConstantBuffer< WorldMatrix >;

//=====================================================================================================================
// @brief	ViewProjMatrix
//=====================================================================================================================
struct ViewProjMatrix
{
    XMMATRIX viewMat;
    XMMATRIX projMat;

    // Construct
    ViewProjMatrix( const XMMATRIX& InViewMat, const XMMATRIX& InProjMat ) : viewMat( InViewMat ), projMat( InProjMat ) {}
};
using ViewProjMatrixBuffer = Dx11ConstantBuffer< ViewProjMatrix >;

//=====================================================================================================================
// @brief	CameraProperty
//=====================================================================================================================
struct CameraProperty
{
    XMFLOAT3 cameraLocation;
    float    padding;

    // Construct
    CameraProperty( const XMFLOAT3& InCameraLocation ) : cameraLocation( InCameraLocation ), padding( 0.0f ) {}
};

using CameraPropertyBuffer = Dx11ConstantBuffer< CameraProperty >;

//=====================================================================================================================
// @brief	PointLightLocation
//=====================================================================================================================
struct PointLightLocation
{
    XMFLOAT4 pointLightLocation[ MaxPointLightCount ];

    // Construct
    PointLightLocation( const XMFLOAT4* InPointLightLocation )
    {
        for ( int i = 0; i < MaxPointLightCount; ++i )
        {
            pointLightLocation[ i ] = InPointLightLocation[ i ];
        }
    }
};

using PointLightLocationBuffer = Dx11ConstantBuffer< PointLightLocation >;

//=====================================================================================================================
// @brief	PointLightColor
//=====================================================================================================================
struct PointLightColor
{
    XMFLOAT4 pointLightColor[ MaxPointLightCount ];

    // Construct
    PointLightColor( const XMFLOAT4* InPointLightColor )
    {
        for ( int i = 0; i < MaxPointLightCount; ++i )
        {
            pointLightColor[ i ] = InPointLightColor[ i ];
        }
    }
};

using PointLightColorBuffer = Dx11ConstantBuffer< PointLightColor >;

//=====================================================================================================================
// @brief	LightProperty
//=====================================================================================================================
struct LightProperty
{
    XMFLOAT4 ambientColor;
    XMFLOAT4 diffuseColor;
    XMFLOAT3 lightDirection;
    float    padding;

    // Construct
    LightProperty( const XMFLOAT4& AmbientColor, const XMFLOAT4& DiffuseColor, const XMFLOAT3& LightDirection ) : ambientColor( AmbientColor ), diffuseColor( DiffuseColor ), lightDirection( LightDirection ), padding( 0.0f ) {}
};
using LightPropertyBuffer = Dx11ConstantBuffer< LightProperty >;

//=====================================================================================================================
// @brief	SpecularProperty
//=====================================================================================================================
struct SpecularProperty
{
    XMFLOAT4 specularColor;
    float    specularPower;
    XMFLOAT3 padding;

    // Construct
    SpecularProperty( const XMFLOAT4& InSpecularColor, float InSpecularPower ) : specularColor( InSpecularColor ), specularPower( InSpecularPower ), padding( 0.0f, 0.0f, 0.0f ) {}
};

using SpecularPropertyBuffer = Dx11ConstantBuffer< SpecularProperty >;