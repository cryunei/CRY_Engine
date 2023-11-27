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

    const std::wstring& wPath = ToWstring( Path );
    HRESULT hr = D3DCompileFromFile( wPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryPoint.c_str(), ShaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, BlobComPtr.GetAddressOf(), &error );

    if ( FAILED( hr ) )
    {
        char* msg = (char * )error->GetBufferPointer();

        return false;
    }

    return true;
}
