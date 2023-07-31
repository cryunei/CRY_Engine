#pragma once


#include "Dx11Resource.h"
#include "../DxCoreInc.h"


class Dx11Shader : public Dx11Resource
{
protected:
    ComPtr< ID3D10Blob > BlobComPtr;

public:
    // Construct
    Dx11Shader() = default;
    Dx11Shader( const Dx11Shader& Other ) = default;
    Dx11Shader( Dx11Shader&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11Shader() override = default;

    // Operators
    Dx11Shader& operator=( const Dx11Shader& Other ) = default;
    Dx11Shader& operator=( Dx11Shader&& Other ) noexcept = default;

    // Create blob
    bool CreateBlob( const std::string& FileName, const std::string& EntryPoint, const std::string& ShaderModel );

    // Release
    virtual void Release() override;

    // Render
    virtual bool Render() const = 0;
    
};
