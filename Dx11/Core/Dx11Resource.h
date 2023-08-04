#pragma once

#include "IDxRenderElement.h"
#include "../DxMacros.h"




//=====================================================================================================================
// @brief	Dx11Resource
//=====================================================================================================================
class Dx11Resource : public IDxRenderElement
{
    CLASS_DEFAULT_BODY( Dx11Resource )

public:
    // Construct
    Dx11Resource() = default;

    // On render
    virtual void OnRender() const override { SetRenderState(); }

    // Set to render state 
    virtual bool SetRenderState() const { return true; }

    // Release
    virtual void Release() = 0;    
};
