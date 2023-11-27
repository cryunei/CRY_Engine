#pragma once

#include "../Asset/CrAsset.h"
#include "../Core/DxTransform.h"


//=====================================================================================================================
// @brief	CrActor
//=====================================================================================================================
class CrActor : public CrAsset
{
protected:
    DxTransform Transform;

public:
    const DxTransform& GetTransform() const { return  Transform; }
    DxTransform*       GetTransform()       { return &Transform; }
    
};
