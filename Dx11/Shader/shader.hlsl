struct PixelIn
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

cbuffer WorldMatrix : register(b0)
{
    matrix worldMat;
};

cbuffer ViewProjMatrix : register(b1)
{
    matrix viewMat;
    matrix projMat;
};

PixelIn VS( float4 position : SV_POSITION, float2 tex : TEXCOORD0 )
{
    PixelIn output;

    output.position = position;
    output.position = mul( position, worldMat );
    output.position = mul( output.position, viewMat );
    output.position = mul( output.position, projMat );
    output.tex = tex;

    return output;
}

Texture2D shaderTexture;
SamplerState SampleType;

float4 PS( float4 position : SV_POSITION, float2 tex : TEXCOORD0 ) : SV_TARGET
{
    float4 textureColor;
    textureColor = shaderTexture.Sample( SampleType, tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    return textureColor;
}