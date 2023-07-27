#include "Dx11ResourceFactory.h"
#include "Dx11Device.h"
#include "../Util/UtilString.h"
#include <d3dcompiler.h>
#include <string>

//=================================================================================================
// @brief	Compile shader
//=================================================================================================
ID3D10Blob* Dx11ResourceFactory::CompileShader( const std::string& Path, const std::string& FuncName, const std::string& ModelName )
{
    ID3D10Blob* vs    = nullptr;
    ID3D10Blob* error = nullptr;

    HRESULT hr = D3DCompileFromFile( ToWstring( Path ).c_str(), nullptr, nullptr, FuncName.c_str(), ModelName.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, &vs, &error );
    if ( FAILED( hr ) )
    {
        char* msg = (char * )error->GetBufferPointer();

        return nullptr;
    }

    return vs;
}

//=================================================================================================
// @brief	Create buffer
//=================================================================================================
bool Dx11ResourceFactory::CreateBuffer( ID3D11Buffer** Buffer, const D3D11_BUFFER_DESC* Desc, const D3D11_SUBRESOURCE_DATA* SubData )
{
    if ( *Buffer )
    {
        (*Buffer)->Release();
        *Buffer = nullptr;
    }

    HRESULT hr = GetDx11Device()->CreateBuffer( Desc, SubData, Buffer );
    if ( FAILED( hr ) )
    {
        return false;
    }

    return true;
}

//=================================================================================================
// @brief	Create constant buffer
//=================================================================================================
bool Dx11ResourceFactory::CreateConstantBuffer( ID3D11Buffer** Buffer, unsigned int Size )
{
    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = Size;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    return CreateBuffer( Buffer, &bd, nullptr );
}
