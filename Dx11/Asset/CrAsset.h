#pragma once


#include <string>


//=====================================================================================================================
// @brief	CrAsset
//=====================================================================================================================
class CrAsset
{
protected:
    std::string Name;

public:
    // Name
    void SetName( const std::string& NewName ) { Name = NewName; }
    const std::string& GetName() const { return Name; }
};
