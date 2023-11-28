#pragma once
#include <string>

class CrLevel;


//=====================================================================================================================
// @brief	CrGame
//=====================================================================================================================
class CrGame
{
private:
    CrLevel* Level = nullptr;
    
public:
    // Load level
    void LoadLevel( const std::string& Path );

    // Tick
    void Tick() const;

};
