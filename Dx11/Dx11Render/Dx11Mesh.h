#pragma once


#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../../Externals/DirectXTK/Inc/WICTextureLoader.h"


#pragma comment ( lib, "d3d11.lib" )
#pragma comment ( lib, "d3dcompiler.lib" )


using namespace DirectX;


class Dx11Mesh
{
private:
    

public:
    // Constructor
    Dx11Mesh();

    // Initialize
    void Initialize( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Render
    void Render( ID3D11DeviceContext* DeviceContext );

private:
    // Initialize Shader
    void _InitializeShader( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );

    // Initialize Texture
    void _InitializeTexutre( ID3D11Device* Device, ID3D11DeviceContext* DeviceContext );
};