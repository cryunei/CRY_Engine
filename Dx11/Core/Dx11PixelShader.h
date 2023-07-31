#pragma once


#include "Dx11Shader.h"


//=====================================================================================================================
// @brief	Dx11PixelShader
//=====================================================================================================================
class Dx11PixelShader : public Dx11Shader
{
private:
    ComPtr< ID3D11PixelShader > ShaderComPtr;

public:
    // Construct
    Dx11PixelShader() = default;
    Dx11PixelShader( const Dx11PixelShader& Other ) = default;
    Dx11PixelShader( Dx11PixelShader&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11PixelShader() override = default;

    // Operators
    Dx11PixelShader& operator=( const Dx11PixelShader& Other ) = default;
    Dx11PixelShader& operator=( Dx11PixelShader&& Other ) noexcept = default;

    // Create shader
    void CreateShader( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel );

    // Release
    virtual void Release() override;

    // Render
    bool Render() const override;

    
};
