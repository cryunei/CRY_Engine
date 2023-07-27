#include "Dx11VertexShader.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"


//=================================================================================================
// @brief	Construct
//=================================================================================================
Dx11VertexShader::Dx11VertexShader()
: VertexShaderBlob ( nullptr )
, VertexShader     ( nullptr )
, InputLayout      ( nullptr )
{
}

//=================================================================================================
// @brief	Create
//=================================================================================================
void Dx11VertexShader::CreateShader( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel )
{
    VertexShaderBlob = Dx11ResourceFactory::CompileShader( FileName, EntryPoint, ShaderModel );
    if ( !VertexShaderBlob ) return;

    GetDx11Device()->CreateVertexShader( VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), nullptr, &VertexShader );    
}

//=================================================================================================
// @brief	Create input layout
//=================================================================================================
void Dx11VertexShader::CreateInputLayout( const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputElements )
{
    if ( !VertexShaderBlob ) return;

    GetDx11Device()->CreateInputLayout( &InputElements[ 0 ], InputElements.size(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &InputLayout );    
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11VertexShader::Release()
{
    SAFE_RELEASE( VertexShaderBlob );
    SAFE_RELEASE( VertexShader );
    SAFE_RELEASE( InputLayout );
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11VertexShader::Render() const
{
    if ( !VertexShader ) return false;
    if ( !InputLayout ) return false;

    GetDx11DeviceContext()->VSSetShader( VertexShader, nullptr, 0 );
    GetDx11DeviceContext()->IASetInputLayout( InputLayout );

    return true;
}
