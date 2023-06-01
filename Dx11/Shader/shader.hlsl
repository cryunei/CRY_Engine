struct PixelIn
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
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

cbuffer LightProperty : register(b2)
{
    float4 diffuseColor;
    float3 lightDirection;
    float  padding;
};

PixelIn VS( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL )
{
    PixelIn output;

    output.position = position;
    output.position = mul( position, worldMat );
    output.position = mul( output.position, viewMat );
    output.position = mul( output.position, projMat );
    output.tex = tex;

    output.normal = mul( normal, (float3x3)worldMat );

    return output;
}

Texture2D shaderTexture;
SamplerState SampleType;

float4 PS( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL ) : SV_TARGET
{
    float4 textureColor;
    textureColor = shaderTexture.Sample( SampleType, tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float3 lightDir = normalize( -lightDirection );
    float lightIntensity = saturate( dot( lightDir, normal ) );
    float4 lightColor = saturate( diffuseColor * lightIntensity );
    
    float4 finalColor = textureColor * lightColor;

    return finalColor;
}