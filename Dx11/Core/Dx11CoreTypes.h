#pragma once


static const int MAX_TEXTURE_REGISTER_COUNT = 128;


//=====================================================================================================================
// @brief	EDx11ResourceType
//=====================================================================================================================
enum class EDx11ResourceType
{
    VertexBuffer,
    IndexBuffer,
    ConstantBuffer,
    DepthStencilBuffer,
    VertexShader,
    PixelShader,
    Texture2D,
    Max,
};
static constexpr int DX11_RESOURCE_TYPE_COUNT = (int)( EDx11ResourceType::Max );


//=====================================================================================================================
// @brief	ERenderPipeLineStage
//=====================================================================================================================
enum class ERenderPipeLineStage
{
    VertexShader,
    PixelShader,
    None,
};