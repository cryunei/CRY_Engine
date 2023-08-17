#pragma once


#include "../DxMacros.h"
#include "../Core/IDxRenderElement.h"


class Dx11Resource;


//=====================================================================================================================
// @brief	Dx11ResourceRenderer
//=====================================================================================================================
class Dx11ResourceRenderer : public IDxRenderElement
{
    CLASS_DEFAULT_BODY( Dx11ResourceRenderer )

protected:
    const Dx11Resource* ResourcePtr;
    int                 RegisterIndex;

public:
    // Construct
    Dx11ResourceRenderer( const Dx11Resource* InResourcePtr, int InRegisterIndex ) : ResourcePtr( InResourcePtr ), RegisterIndex( InRegisterIndex ) {}

    // On render
    virtual void OnRender() const override;

    // Get resource ptr
    const Dx11Resource* GetResourcePtr() const { return ResourcePtr; }

    // Get register index
    int GetRegisterIndex() const { return RegisterIndex; }
};
