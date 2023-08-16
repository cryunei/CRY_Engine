#include "Dx11Shader.h"
#include "../Util/UtilString.h"
#include <d3dcompiler.h>


//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11Shader::Release()
{
    BlobComPtr.Reset();
}

//=====================================================================================================================
// @brief	Create blob
//=====================================================================================================================
bool Dx11Shader::CreateBlob( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel )
{
    Release();

    ID3D10Blob* error = nullptr;

    HRESULT hr = D3DCompileFromFile( ToWstring( Path ).c_str(), nullptr, nullptr, EntryPoint.c_str(), ShaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, &BlobComPtr, &error );
    if ( FAILED( hr ) )
    {
        char* msg = (char * )error->GetBufferPointer();

        return false;
    }

    return true;
}
