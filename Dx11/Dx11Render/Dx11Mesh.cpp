#include "Dx11Mesh.h"


//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Dx11Mesh::Dx11Mesh()
    : PixelShader( nullptr )
{}

//------------------------------------------------------------------------------
// Initialize
//------------------------------------------------------------------------------
void Dx11Mesh::Initialize( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    _InitializeShader( Device, DeviceContext );
    _InitializeTexutre( Device, DeviceContext );
}

//------------------------------------------------------------------------------
// _InitializeShader
//------------------------------------------------------------------------------
void Dx11Mesh::_InitializeShader( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    ID3D10Blob* ps = nullptr;
    ID3D10Blob* error = nullptr;

    D3DCompileFromFile( L"Shader/shader.hlsl", nullptr, nullptr, "PS", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &ps, &error );

    Device->CreatePixelShader ( ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &PixelShader  );

    DeviceContext->PSSetShader( PixelShader,  0, 0 );
}

//------------------------------------------------------------------------------
// _InitializeTexutre
//------------------------------------------------------------------------------
void Dx11Mesh::_InitializeTexutre( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext )
{
    // create texture
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory( &td, sizeof( D3D11_TEXTURE2D_DESC ) );

    td.Height = 800;
    td.Width = 480;
    td.MipLevels = 0;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    td.CPUAccessFlags = 0;
    td.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    Device->CreateTexture2D( &td, nullptr, &Texture );

    // create sample state
    ID3D11SamplerState* SampleState;

    D3D11_SAMPLER_DESC sd;
    ZeroMemory( &sd, sizeof( D3D11_SAMPLER_DESC ) );

    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MipLODBias = 0.0f;
    sd.MaxAnisotropy = 1;
    sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sd.BorderColor[ 0 ] = 0;
    sd.BorderColor[ 1 ] = 0;
    sd.BorderColor[ 2 ] = 0;
    sd.BorderColor[ 3 ] = 0;
    sd.MinLOD = 0;
    sd.MaxLOD = D3D11_FLOAT32_MAX;

    // Create the texture sampler state.
    Device->CreateSamplerState( &sd, &SampleState );

    CoInitialize( nullptr );

    CreateWICTextureFromFile( Device, L"Resource/Texture/SampleTexture.png", &TextureResource, &TextureView );

    DeviceContext->PSSetShaderResources( 0, 1, &TextureView );
    DeviceContext->PSSetSamplers(0, 1, &SampleState );
}
