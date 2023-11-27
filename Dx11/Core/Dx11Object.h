#pragma once


#include "../DxMacros.h"
#include <string>

class CrAsset;


//=====================================================================================================================
// @brief	Dx11Object
//=====================================================================================================================
class Dx11Object
{
    CLASS_DEFAULT_BODY( Dx11Object )

private:
    std::string Name;

public:
    // Construct
    Dx11Object() = default;

    // Destructor
    virtual ~Dx11Object() = default;

    // Create from
    virtual bool CreateFrom( const CrAsset* Asset ) { return true; }

    // Release
    virtual void Release() = 0;

    // Name
    void SetName( const std::string& InName ) { Name = InName; }
    const std::string& GetName() const { return Name; }
};
