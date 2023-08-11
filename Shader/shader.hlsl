#define NUM_POINT_LIGHTS 4

struct PixelIn
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float3 pointLightLocation[ NUM_POINT_LIGHTS ] : TEXCOORD2;
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

cbuffer CameraProperty : register(b2)
{
    float3 cameraLocation;
    float  padding_cp;
};

cbuffer PointLightLocation : register(b3)
{
    float4 pointLightLocation[ NUM_POINT_LIGHTS ];
};

cbuffer LightProperty : register(b0)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float  padding_lp;
};

cbuffer SpecularProperty : register(b1)
{
    float4 specularColor;
    float  specularPower;
    float3 padding_sp;
};

cbuffer PointLightColor : register(b2)
{
    float4 pointLightColor[ NUM_POINT_LIGHTS ];
};

//------------------------------------------------------------------------------
// Lambert
//------------------------------------------------------------------------------
PixelIn VS( float4 position : SV_POSITION, float2 tex : TEXCOORD0, float3 normal : NORMAL )
{
    PixelIn output;
    float4 worldLocation = mul( position, worldMat );
    
    output.position = worldLocation;
    output.position = mul( output.position, viewMat );
    output.position = mul( output.position, projMat );
    
    output.normal = mul( normal, (float3x3)worldMat );

    output.tex = tex;
    output.viewDirection = normalize( cameraLocation - worldLocation.xyz );    

    for ( int i = 0; i < NUM_POINT_LIGHTS; ++i )
    {
        output.pointLightLocation[ i ] = normalize( pointLightLocation[ i ].xyz - worldLocation.xyz );
    }

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
// Specular
//------------------------------------------------------------------------------
float4 PS_Specular( PixelIn input ) : SV_TARGET
{
    float4 textureColor = float4( 1.f, 1.f, 1.f, 1.f );
    textureColor = shaderTexture.Sample( SampleType, input.tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float3 lightDir = normalize( -lightDirection );
    float lightIntensity = saturate( dot( lightDir, input.normal ) );

    // half lambert
    lightIntensity = lightIntensity * 0.5 + 0.5;
    lightIntensity = pow( lightIntensity, 3.f );

    float4 lightColor = saturate( ambientColor + ( diffuseColor * lightIntensity ) );

    // R = p + 2n(-p dot n)
    float3 reflection = reflect( lightDir, input.normal ); // normalize( lightDir + 2.f * normal * dot( -lightDir, normal ) );
    float4 specular = specularColor * pow( saturate( dot( reflection, input.viewDirection ) ), specularPower );
    
    float4 finalColor = textureColor * lightColor;
    finalColor = saturate( finalColor + specular );

    return finalColor;
}

//------------------------------------------------------------------------------
// PointLight
//------------------------------------------------------------------------------
float4 PS_PointLight( PixelIn input ) : SV_TARGET
{
    float4 textureColor = float4( 1.f, 1.f, 1.f, 1.f );
    textureColor = shaderTexture.Sample( SampleType, input.tex );
    textureColor = pow( textureColor, 1.f/2.2f );

    float lightIntensity[ NUM_POINT_LIGHTS ];
    float4 lightColor[ NUM_POINT_LIGHTS ];
        
    int i;
    for ( i = 0; i < NUM_POINT_LIGHTS; ++i )
    {
        lightIntensity[ i ] = saturate( dot( input.normal, input.pointLightLocation[ i ] ) );
        lightIntensity[ i ] = lightIntensity[ i ] * 0.5 + 0.5;
        lightIntensity[ i ] = pow( lightIntensity[ i ], 3.f );
        lightColor[ i ] = pointLightColor[ i ] * lightIntensity[ i ];
    }

    float4 colorSum = float4( 0.f, 0.f, 0.f, 1.f );
    for ( i = 0; i < NUM_POINT_LIGHTS; ++i )
    {
        colorSum.r += lightColor[ i ].r;
        colorSum.g += lightColor[ i ].g;
        colorSum.b += lightColor[ i ].b;
    }
    
    float4 finalColor = textureColor * saturate( colorSum );

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
    lightIntensity = lightIntensity * 5.f;
    lightIntensity = ceil( lightIntensity );
    lightIntensity = lightIntensity / 5.f;
    
    float4 lightColor = saturate( diffuseColor * lightIntensity );
    
    float4 finalColor = textureColor * lightColor;

    return finalColor;
}