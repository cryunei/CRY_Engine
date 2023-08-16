#pragma once


#include "../DxMacros.h"


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

    // Release
    virtual void Release() = 0;
};
