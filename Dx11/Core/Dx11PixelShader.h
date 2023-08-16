#pragma once


#include "Dx11Shader.h"


//=====================================================================================================================
// @brief	Dx11PixelShader
//=====================================================================================================================
class Dx11PixelShader : public Dx11Shader
{
    CLASS_DEFAULT_BODY( Dx11PixelShader )

private:
    ComPtr< ID3D11PixelShader > ShaderComPtr;

public:
    // Construct
    Dx11PixelShader() = default;

    // Create shader
    void CreateShader( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel );

    // Release
    virtual void Release() override;

    // Set shader 
    virtual void SetShader() const override;

    
};
