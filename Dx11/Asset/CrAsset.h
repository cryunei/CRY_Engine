#pragma once

#include "CrAssetTypes.h"
#include <string>


//=====================================================================================================================
// @brief	CrAsset
//=====================================================================================================================
class CrAsset
{
protected:
    std::string  Name;
    ECrAssetType Type;

public:
    // Name
    void SetName( const std::string& NewName ) { Name = NewName; }
    const std::string& GetName() const { return Name; }

    // Type
    void SetType( ECrAssetType NewType ) { Type = NewType; }
    ECrAssetType GetType() const { return Type; }
};
