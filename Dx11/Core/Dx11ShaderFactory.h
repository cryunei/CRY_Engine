#pragma once


#include <d3d11.h>

#pragma comment ( lib, "d3d11.lib" )


class Dx11ShaderFactory
{
public:
    // Compile shader
    static ID3D10Blob* CompileShader( const LPCWSTR& Path, const LPCSTR& FuncName, const LPCSTR& ModelName );    
};
