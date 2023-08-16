#pragma once


#include "../DxTypes.h"
#include "../DxMacros.h"
#include "Dx11Resource.h"


//=====================================================================================================================
// @brief	Dx11Texture2D
//=====================================================================================================================
class Dx11Texture2D : public Dx11Resource
{
    CLASS_DEFAULT_BODY( Dx11Texture2D )

private:
    ComPtr< ID3D11Texture2D           > Texture2DComPtr;
    ComPtr< ID3D11Resource            > TextureResourceComPtr;
    ComPtr< ID3D11ShaderResourceView  > TextureSRVComPtr;
    ComPtr< ID3D11SamplerState        > TextureSSComPtr;

    D3D11_TEXTURE2D_DESC Desc;

public:
    // Construct
    Dx11Texture2D() = default;

    // Release
    virtual void Release() override;

    // Create texture
    void CreateTexture( const std::string& TexturePath, DXGI_FORMAT Format, UINT Width, UINT Height, UINT SamplingCount );

    // Set to render state 
    virtual bool SetRenderState( int InRegisterIndex ) const override;

    
};
