#include "Dx11PixelShader.h"
#include "Dx11Device.h"


//=====================================================================================================================
// @brief	Create shader
//=====================================================================================================================
void Dx11PixelShader::CreateShader( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel )
{
    if ( CreateBlob( FileName, EntryPoint, ShaderModel ) )
    {
        HRESULT hr = GetDx11Device()->CreatePixelShader( BlobComPtr->GetBufferPointer(), BlobComPtr->GetBufferSize(), nullptr, ShaderComPtr.GetAddressOf() );
        if ( FAILED( hr ) )
        {
            int i = 0;
        }
    }
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11PixelShader::Release()
{
    Dx11Shader::Release();

    ShaderComPtr.Reset();
}

//=====================================================================================================================
// @brief	Set shader
//=====================================================================================================================
void Dx11PixelShader::SetShader() const
{
    GetDx11DeviceContext()->PSSetShader( ShaderComPtr.Get(), nullptr, 0 );
}
