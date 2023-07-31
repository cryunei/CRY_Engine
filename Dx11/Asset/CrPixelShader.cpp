#include "CrPixelShader.h"


//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void CrPixelShader::Initialize( std::string InFileName, std::string InEntryPoint, std::string InShaderModel )
{
    FileName = std::move( InFileName );
    EntryPoint = std::move( InEntryPoint );
    ShaderModel = std::move( InShaderModel );
}
