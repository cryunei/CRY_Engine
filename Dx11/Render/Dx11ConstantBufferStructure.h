#pragma once


#include "../Core/Dx11ConstantBuffer.h"


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
// @brief	LightProperty
//=====================================================================================================================
struct LightProperty
{
    XMFLOAT4 diffuseColor;
    XMFLOAT3 lightDirection;
    float    padding;

    // Construct
    LightProperty( const XMFLOAT4& InDiffuseColor, const XMFLOAT3& InLightDirection ) : diffuseColor( InDiffuseColor ), lightDirection( InLightDirection ), padding( 0.0f ) {}
};
using LightPropertyBuffer = Dx11ConstantBuffer< LightProperty >;