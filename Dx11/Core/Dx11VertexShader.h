#pragma once


#include "Dx11Shader.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11VertexShader
//=====================================================================================================================
class Dx11VertexShader : public Dx11Shader
{
private:
    ComPtr< ID3D11VertexShader > ShaderComPtr;
    ComPtr< ID3D11InputLayout  > InputLayoutComPtr;

public:
    // Construct
    Dx11VertexShader() = default;
    Dx11VertexShader( const Dx11VertexShader& Other ) = default;
    Dx11VertexShader( Dx11VertexShader&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11VertexShader() override = default;

    // Operators
    Dx11VertexShader& operator=( const Dx11VertexShader& Other ) = default;
    Dx11VertexShader& operator=( Dx11VertexShader&& Other ) noexcept = default;

    // Create shader
    void CreateShader( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel );

    // Create input layout
    void CreateInputLayout( const std::vector< D3D11_INPUT_ELEMENT_DESC >& InputElements );

    // Release
    virtual void Release() override;

    // Render
    bool Render() const override;
    
};
