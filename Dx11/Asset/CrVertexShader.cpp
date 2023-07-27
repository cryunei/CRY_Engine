#include "CrVertexShader.h"


//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void CrVertexShader::Initialize( std::string InFileName, std::string InEntryPoint, std::string InShaderModel, std::vector<D3D11_INPUT_ELEMENT_DESC> InInputElements )
{
    FileName = std::move( InFileName );
    EntryPoint = std::move( InEntryPoint );
    ShaderModel = std::move( InShaderModel );
    InputElements = std::move( InInputElements );
}
