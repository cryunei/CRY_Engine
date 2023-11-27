#include "Dx11LevelLoader.h"
#include "../Dx11.h"
#include "../Actor/CrMeshActor.h"
#include "../Actor/CrReflector.h"
#include "../Level/CrLevel.h"
#include "../Render/Dx11ReflectionRenderer.h"
#include "../Render/Dx11Renderer.h"


//=====================================================================================================================
// @brief	Load
//=====================================================================================================================
void Dx11LevelLoader::Load( CrLevel& InLevel, Dx11Renderer& InRenderer )
{
    for ( const CrReflector* crReflector : InLevel.GetReflectors() )
    {
        G_Dx11ReflectionRenderer.AddReflector( crReflector->GetName(), crReflector->GetTransform(), crReflector->GetWidth(), crReflector->GetHeight(), crReflector->GetIntensity() );
    }

    for ( const CrMeshActor* crMeshActor : InLevel.GetMeshes() )
    {
        for ( const std::string& renderTarget : crMeshActor->GetRenderTargets() )
        {
            InRenderer.AddMeshRenderElement( *crMeshActor, renderTarget );
        }

        if ( crMeshActor->CanReflect() )
        {
            G_Dx11ReflectionRenderer.AddMeshRenderElement( *crMeshActor );
        }
    }

    InRenderer.SortRenderQueue();
}