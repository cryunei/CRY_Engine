#pragma once


//=====================================================================================================================
// @brief	ECrAssetType
//=====================================================================================================================
enum class ECrAssetType
{
    Primitive,
    VertexShader,
    PixelShader,
    Texture2D,
    Mesh,
    Max,
};

static constexpr int CRASSET_TYPE_COUNT = (int)( ECrAssetType::Max );