#pragma once


#include "Dx11Object.h"


//=====================================================================================================================
// @brief	Dx11Resource
//=====================================================================================================================
class Dx11Resource : public Dx11Object
{
    CLASS_DEFAULT_BODY( Dx11Resource )

public:
    // Construct
    Dx11Resource() = default;

    // Set render state
    virtual bool SetRenderState( int InRegisterIndex ) const = 0;
};
