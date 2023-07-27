#pragma once


#include "CrAsset.h"
#include <d3d11.h>
#include <string>
#include <vector>


class CrVertexShader : public CrAsset
{
private:
    std::string FileName;    // hlsl file name
    std::string EntryPoint;  // hlsl entry point
    std::string ShaderModel; // hlsl shader model

    std::vector< D3D11_INPUT_ELEMENT_DESC > InputElements; // input elements

public:
    // Constructor
    CrVertexShader() = default;
    CrVertexShader( const CrVertexShader& Other ) = default;
    CrVertexShader( CrVertexShader&& Other ) noexcept = default;

    // Destructor
    ~CrVertexShader() = default;

    // operators
    CrVertexShader& operator=( const CrVertexShader& Other ) = default;
    CrVertexShader& operator=( CrVertexShader&& Other ) noexcept = default;

    // Initialize
    void Initialize( std::string InFileName, std::string InEntryPoint, std::string InShaderModel, std::vector< D3D11_INPUT_ELEMENT_DESC > InInputElements );

    // Get file name
    const std::string& GetFileName() const { return FileName; }

    // Get entry point
    const std::string& GetEntryPoint() const { return EntryPoint; }

    // Get shader model
    const std::string& GetShaderModel() const { return ShaderModel; }

    // Get input elements
    const std::vector< D3D11_INPUT_ELEMENT_DESC >& GetInputElements() const { return InputElements; }
};
