#pragma once


#include <d3d11.h>
#include <string>


#pragma comment ( lib, "d3d11.lib" )


//=====================================================================================================================
// @brief	Dx11ResourceFactory
//=====================================================================================================================
class Dx11ResourceFactory
{
public:
    // Compile shader
    static ID3D10Blob* CompileShader( const std::string& Path, const std::string& FuncName, const std::string& ModelName );

    // Create buffer
    static bool CreateBuffer( ID3D11Buffer** Buffer, const D3D11_BUFFER_DESC* Desc, const D3D11_SUBRESOURCE_DATA* SubData );

    // Create constant buffer
    static bool CreateConstantBuffer( ID3D11Buffer** Buffer, unsigned int Size );
};