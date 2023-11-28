#pragma once


#include <Windows.h>


//=====================================================================================================================
// @brief	CrTimerManager
//=====================================================================================================================
class CrTimerManager
{
private:
    float DeltaTime = 0.0f;
    LARGE_INTEGER Frequency;
    LARGE_INTEGER LastTime;

public:
    // Constructor
    CrTimerManager();

    // Pre tick
    void PreTick();

    // Post tick
    void PostTick();

    // Get delta time
    float GetDeltaTime() const { return DeltaTime; }    
};


//=====================================================================================================================
// @brief	GetTimerManager
//=====================================================================================================================
CrTimerManager* GetTimerManager();
