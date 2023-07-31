#pragma once


#include "../DxTypes.h"
#include "Dx11Resource.h"


class Dx11Texture2D : public Dx11Resource
{
private:
    ComPtr< ID3D11Texture2D           > Texture2DComPtr;
    ComPtr< ID3D11Resource            > TextureResourceComPtr;
    ComPtr< ID3D11ShaderResourceView  > TextureSRVComPtr;
    ComPtr< ID3D11SamplerState        > TextureSSComPtr;

    D3D11_TEXTURE2D_DESC Desc;

public:
    // Construct
    Dx11Texture2D() = default;
    Dx11Texture2D( const Dx11Texture2D& Other ) = default;
    Dx11Texture2D( Dx11Texture2D&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11Texture2D() override = default;

    // Operators
    Dx11Texture2D& operator=( const Dx11Texture2D& Other ) = default;
    Dx11Texture2D& operator=( Dx11Texture2D&& Other ) noexcept = default;

    // Create texture
    void CreateTexture( const std::string& TexturePath, DXGI_FORMAT Format, UINT Width, UINT Height, UINT SamplingCount );

    // Release
    virtual void Release() override;

    // Render
    bool Render() const;

    
};
