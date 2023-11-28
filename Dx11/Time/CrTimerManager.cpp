#include "CrTimerManager.h"


CrTimerManager G_TimerManager;
CrTimerManager* GetTimerManager() { return &G_TimerManager; }


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrTimerManager::CrTimerManager()
{
    QueryPerformanceFrequency( &Frequency );
    QueryPerformanceCounter( &LastTime );
}

//=====================================================================================================================
// @brief	Pre tick
//=====================================================================================================================
void CrTimerManager::PreTick()
{
    QueryPerformanceCounter( &LastTime );
}

//=====================================================================================================================
// @brief	Post tick
//=====================================================================================================================
void CrTimerManager::PostTick()
{
    LARGE_INTEGER currTime;
    QueryPerformanceCounter( &currTime );

    DeltaTime = (float)( currTime.QuadPart - LastTime.QuadPart ) / (float)Frequency.QuadPart; 
}
