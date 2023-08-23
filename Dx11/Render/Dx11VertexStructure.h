#pragma once


#include "../DxCoreInc.h"


//=====================================================================================================================
// @brief	Vertex_Diffuse
//=====================================================================================================================
struct Vertex_Diffuse
{
    XMFLOAT3 Position;  // position
    XMFLOAT2 TextureUV; // texture uv
    XMFLOAT3 Normal;    // normal
};

//=====================================================================================================================
// @brief	Vertex_NormalMap
//=====================================================================================================================
struct Vertex_NormalMap
{
    XMFLOAT3 Position;  // position
    XMFLOAT2 TextureUV; // texture uv
    XMFLOAT3 Normal;    // normal
    XMFLOAT3 Tangent;   // tangent
    XMFLOAT3 Binormal;  // binormal
};

