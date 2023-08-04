#pragma once


#include "Dx11Shader.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11VertexShader
//=====================================================================================================================
class Dx11VertexShader : public Dx11Shader
{
private:
    CLASS_DEFAULT_BODY( Dx11VertexShader )

private:
    ComPtr< ID3D11VertexShader > ShaderComPtr;
    ComPtr< ID3D11InputLayout  > InputLayoutComPtr;

public:
    // Construct
    Dx11VertexShader() = default;

    // Destructor
    ~Dx11VertexShader() override = default;

    // Create shader
    void CreateShader( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel );

    // Create input layout
    void CreateInputLayout( const std::vector< D3D11_INPUT_ELEMENT_DESC >& InputElements );

    // Release
    virtual void Release() override;

    // Set to render state
    virtual bool SetRenderState() const override;
    
};
