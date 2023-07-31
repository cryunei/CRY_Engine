#pragma once


#include "../DxTypes.h"
#include "CrAsset.h"


class CrTexture2D : public CrAsset
{
private:
    std::string  Path;
    unsigned int Width;
    unsigned int Height;
    DXGI_FORMAT  Format;
    unsigned int SamplingCount;

public:
    // Construct
    CrTexture2D() = default;
    CrTexture2D( const CrTexture2D& Other ) = default;
    CrTexture2D( CrTexture2D&& Other ) noexcept = default;

    // Destruct
    virtual ~CrTexture2D() = default;

    // Operators
    CrTexture2D& operator=( const CrTexture2D& Other ) = default;
    CrTexture2D& operator=( CrTexture2D&& Other ) noexcept = default;

    // Path
    const std::string& GetPath() const { return Path; }
    void SetPath( const std::string& FileName ) { this->Path = FileName; }

    // Width
    unsigned GetWidth() const { return Width; }
    void SetWidth( const unsigned Width ) { this->Width = Width; }

    // Height
    unsigned GetHeight() const { return Height; }
    void SetHeight( const unsigned Height ) { this->Height = Height; }

    // Formnat
    DXGI_FORMAT GetFormat() const { return Format; }
    void SetFormat( const DXGI_FORMAT Format ) { this->Format = Format; }

    // Sampling count
    unsigned GetSamplingCount() const { return SamplingCount; }
    void SetSamplingCount( const unsigned SamplingCount ) { this->SamplingCount = SamplingCount; }    
};
