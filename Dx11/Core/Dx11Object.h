#pragma once


#include "../DxMacros.h"


class CrAsset;


//=====================================================================================================================
// @brief	Dx11Object
//=====================================================================================================================
class Dx11Object
{
    CLASS_DEFAULT_BODY( Dx11Object )

public:
    // Construct
    Dx11Object() = default;

    // Destructor
    virtual ~Dx11Object() = default;

    // Create from
    virtual bool CreateFrom( const CrAsset* Asset ) { return true; }

    // Release
    virtual void Release() = 0;
};
