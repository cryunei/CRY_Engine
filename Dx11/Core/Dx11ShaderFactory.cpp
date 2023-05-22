#include "Dx11ShaderFactory.h"
#include "Dx11Device.h"
#include <d3dcompiler.h>


//=================================================================================================
// @brief	Compile shader
//=================================================================================================
ID3D10Blob* Dx11ShaderFactory::CompileShader( const LPCWSTR& Path, const LPCSTR& FuncName, const LPCSTR& ModelName )
{
    ID3D10Blob* vs    = nullptr;
    ID3D10Blob* error = nullptr;

    HRESULT hr = D3DCompileFromFile( Path, nullptr, nullptr, FuncName, ModelName, D3DCOMPILE_ENABLE_STRICTNESS, 0, &vs, &error );
    if ( FAILED( hr ) )
    {
        char* msg = (char * )error->GetBufferPointer();

        return nullptr;
    }

    return vs;
}