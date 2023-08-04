#pragma once


#include "Dx11Resource.h"
#include "../DxCoreInc.h"


//=====================================================================================================================
// @brief	Dx11Shader
//=====================================================================================================================
class Dx11Shader : public Dx11Resource
{
    CLASS_DEFAULT_BODY( Dx11Shader )

protected:
    ComPtr< ID3D10Blob > BlobComPtr;

public:
    // Construct
    Dx11Shader() = default;

    // Destructor
    ~Dx11Shader() override = default;

    // Create blob
    bool CreateBlob( const std::string& Path, const std::string& EntryPoint, const std::string& ShaderModel );

    // Release
    virtual void Release() override;
    
};
