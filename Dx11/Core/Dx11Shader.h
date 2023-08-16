#pragma once


#include "Dx11Resource.h"
#include "IDxRenderElement.h"
#include "../DxCoreInc.h"


//=====================================================================================================================
// @brief	Dx11Shader
//=====================================================================================================================
class Dx11Shader : public Dx11Object, public IDxRenderElement
{
    CLASS_DEFAULT_BODY( Dx11Shader )

protected:
    ComPtr< ID3D10Blob > BlobComPtr;

public:
    // Constructor
    Dx11Shader() = default;

    // Destructor
    ~Dx11Shader() override = default;

    // Release
    virtual void Release() override;

    // Create blob
    bool CreateBlob( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel );

    // On render
    virtual void OnRender() const override { SetShader(); }

    // Set shader
    virtual void SetShader() const = 0;
};
