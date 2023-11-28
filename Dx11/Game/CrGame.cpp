#include "CrGame.h"
#include "../Dx11.h"
#include "../Level/CrLevel.h"
#include "../Loader/Dx11LevelLoader.h"
#include "../Render/Dx11ReflectionRenderer.h"
#include "../Time/CrTimerManager.h"


//=====================================================================================================================
// @brief	Load level
//=====================================================================================================================
void CrGame::LoadLevel( const std::string& Path )
{
    if ( !Level )
    {
        Level = new CrLevel();
    }

    Level->Release();
    Level->LoadFromJson( Path );

    Dx11LevelLoader::Load( *Level, G_Dx11Renderer );
    G_Dx11ReflectionRenderer.SortRenderQueue();
}

//=====================================================================================================================
// @brief	Tick
//=====================================================================================================================
void CrGame::Tick() const
{
    if ( Level )
    {
        Level->Tick( GetTimerManager()->GetDeltaTime() );
    }
}


