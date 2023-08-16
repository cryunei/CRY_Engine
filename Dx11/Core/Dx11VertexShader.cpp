#include "Dx11VertexShader.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"


//=====================================================================================================================
// @brief	Create shader
//=====================================================================================================================
void Dx11VertexShader::CreateShader( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel )
{
    if ( CreateBlob( Path, EntryPoint, ShaderModel ) )
    {
        GetDx11Device()->CreateVertexShader( BlobComPtr->GetBufferPointer(), BlobComPtr->GetBufferSize(), nullptr, &ShaderComPtr );
    }    
}

//=====================================================================================================================
// @brief	Create input layout
//=====================================================================================================================
void Dx11VertexShader::CreateInputLayout( const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputElements )
{
    if ( !BlobComPtr.Get() ) return;

    GetDx11Device()->CreateInputLayout( &InputElements[ 0 ], (UINT)( InputElements.size() ), BlobComPtr->GetBufferPointer(), BlobComPtr->GetBufferSize(), &InputLayoutComPtr );    
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11VertexShader::Release()
{
    Dx11Shader::Release();

    ShaderComPtr.Reset();
    InputLayoutComPtr.Reset();
}

//=====================================================================================================================
// @brief	Set shader
//=====================================================================================================================
void Dx11VertexShader::SetShader() const
{
    if ( !ShaderComPtr.Get() ) return;
    if ( !InputLayoutComPtr.Get() ) return;

    GetDx11DeviceContext()->VSSetShader( ShaderComPtr.Get(), nullptr, 0 );
    GetDx11DeviceContext()->IASetInputLayout( InputLayoutComPtr.Get() );
}
