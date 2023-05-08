struct PixelIn
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelIn VS( float4 position : SV_POSITION, float2 tex : TEXCOORD0 )
{
    PixelIn output;

    output.position = position;
    output.tex = tex;

    return output;
}

Texture2D shaderTexture;
SamplerState SampleType;

float4 PS( float4 position : SV_POSITION, float2 tex : TEXCOORD0 ) : SV_TARGET
{
    float4 textureColor;
    textureColor = shaderTexture.Sample( SampleType, tex );

    return textureColor;
}