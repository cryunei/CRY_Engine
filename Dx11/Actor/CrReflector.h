#pragma once


#include "CrMeshActor.h"


//=====================================================================================================================
// @brief	CrReflector
//=====================================================================================================================
class CrReflector : public CrMeshActor
{
private:
    unsigned int Width     = 1024;
    unsigned int Height    = 1024;
    float        Intensity = 0.25f;

public:
    // Name
    void SetName( const std::string& InName ) { Name = InName; }
    const std::string& GetName() const { return Name; }

    // Width
    void SetWidth( unsigned int InWidth ) { Width = InWidth; }
    unsigned int GetWidth() const { return Width; }

    // Height
    void SetHeight( unsigned int InHeight ) { Height = InHeight; }
    unsigned int GetHeight() const { return Height; }

    // Intensity
    void SetIntensity( float InIntensity ) { Intensity = InIntensity; }
    float GetIntensity() const { return Intensity; }


};
