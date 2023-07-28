#include "Dx11VertexShader.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ResourceFactory.h"


//=================================================================================================
// @brief	Construct
//=================================================================================================
Dx11VertexShader::Dx11VertexShader()
: ShaderBlob ( nullptr )
, Shader     ( nullptr )
, InputLayout      ( nullptr )
{
}

//=================================================================================================
// @brief	Create
//=================================================================================================
void Dx11VertexShader::CreateShader( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel )
{
    ShaderBlob = Dx11ResourceFactory::CompileShader( FileName, EntryPoint, ShaderModel );
    if ( !ShaderBlob ) return;

    GetDx11Device()->CreateVertexShader( ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &Shader );    
}

//=================================================================================================
// @brief	Create input layout
//=================================================================================================
void Dx11VertexShader::CreateInputLayout( const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputElements )
{
    if ( !ShaderBlob ) return;

    GetDx11Device()->CreateInputLayout( &InputElements[ 0 ], InputElements.size(), ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), &InputLayout );    
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11VertexShader::Release()
{
    SAFE_RELEASE( ShaderBlob );
    SAFE_RELEASE( Shader );
    SAFE_RELEASE( InputLayout );
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11VertexShader::Render() const
{
    if ( !Shader ) return false;
    if ( !InputLayout ) return false;

    GetDx11DeviceContext()->VSSetShader( Shader, nullptr, 0 );
    GetDx11DeviceContext()->IASetInputLayout( InputLayout );

    return true;
}
