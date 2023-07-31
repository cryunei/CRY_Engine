#pragma once


#include "CrAsset.h"
#include <string>


class CrPixelShader : public CrAsset
{
private:
    std::string FileName;    // hlsl file name
    std::string EntryPoint;  // hlsl entry point
    std::string ShaderModel; // hlsl shader model

public:
    // Constructor
    CrPixelShader() = default;
    CrPixelShader( const CrPixelShader& Other ) = default;
    CrPixelShader( CrPixelShader&& Other ) noexcept = default;

    // Destructor
    ~CrPixelShader() = default;

    // operators
    CrPixelShader& operator=( const CrPixelShader& Other ) = default;
    CrPixelShader& operator=( CrPixelShader&& Other ) noexcept = default;

    // Initialize
    void Initialize( std::string InFileName, std::string InEntryPoint, std::string InShaderModel );

    // Get file name
    const std::string& GetFileName() const { return FileName; }

    // Get entry point
    const std::string& GetEntryPoint() const { return EntryPoint; }

    // Get shader model
    const std::string& GetShaderModel() const { return ShaderModel; }
        
    
};
