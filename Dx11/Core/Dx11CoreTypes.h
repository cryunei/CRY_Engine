#pragma once


static const int MAX_TEXTURE_REGISTER_COUNT = 128;


//=====================================================================================================================
// @brief	ERenderPipeLineStage
//=====================================================================================================================
enum class ERenderPipeLineStage
{
    VertexShader,
    PixelShader,
    None,
};