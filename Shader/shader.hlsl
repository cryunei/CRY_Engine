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
    
    output.normal = mul( normal, (float3x3)worldMat );

    output.tex = tex;

    return output;
}

Texture2D shaderTexture;
SamplerState SampleType;

//------------------------------------------------------------------------------
// Lambert
//------------------------------------------------------------------------------
float4 PS( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL ) : SV_TARGET
{
    float4 textureColor = float4( 1.f, 1.f, 1.f, 1.f );
    textureColor = shaderTexture.Sample( SampleType, tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float3 lightDir = normalize( -lightDirection );
    float lightIntensity = saturate( dot( lightDir, normal ) );    
    float4 lightColor = saturate( diffuseColor * lightIntensity );
    
    float4 finalColor = textureColor * lightColor;

    return finalColor;
}

//------------------------------------------------------------------------------
// Half Lambert
//------------------------------------------------------------------------------
float4 PS_HalfLambert( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL ) : SV_TARGET
{
    float4 textureColor = float4( 1.f, 1.f, 1.f, 1.f );
    textureColor = shaderTexture.Sample( SampleType, tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float3 lightDir = normalize( -lightDirection );
    float lightIntensity = saturate( dot( lightDir, normal ) );

    // half lambert
    lightIntensity = lightIntensity * 0.5 + 0.5;
    lightIntensity = pow( lightIntensity, 2.f );
    
    float4 lightColor = saturate( diffuseColor * lightIntensity );
    
    float4 finalColor = textureColor * lightColor;

    return finalColor;
}

//------------------------------------------------------------------------------
// Toon
//------------------------------------------------------------------------------
float4 PS_Toon( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL ) : SV_TARGET
{
    float4 textureColor = float4( 1.f, 1.f, 1.f, 1.f );
    textureColor = shaderTexture.Sample( SampleType, tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float3 lightDir = normalize( -lightDirection );
    float lightIntensity = saturate( dot( lightDir, normal ) );

    // half lambert
    lightIntensity = lightIntensity * 0.5 + 0.5;
    lightIntensity = pow( lightIntensity, 2.f );

    // toon
    lightIntensity = lightIntensity * 3.f;
    lightIntensity = ceil( lightIntensity );
    lightIntensity = lightIntensity / 3.f;
    
    float4 lightColor = saturate( diffuseColor * lightIntensity );
    
    float4 finalColor = textureColor * lightColor;

    return finalColor;
}