#include "DevTestUI.h"
#include "imgui.h"
#include "../Dx11.h"
#include "../Core/DxTransform.h"
#include "../Render/Dx11Renderer.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
DevTestUI::DevTestUI()
{
    const Vector3& lightDir = G_Dx11Renderer.GetLight()->GetDirection();
    LightDirection[ 0 ] = lightDir.x;
    LightDirection[ 1 ] = lightDir.y;
    LightDirection[ 2 ] = lightDir.z;
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void DevTestUI::Render()
{
    CameraTransformEditor.Render();

    if ( ImGui::Button( "View Center" ) )
    {
        G_Dx11Renderer.GetCamera()->LookAt( Vector3::Zero );
        CameraTransformEditor.Sync();
    }

    if ( ImGui::SliderFloat3( "Light Direction", LightDirection, -1.f, 1.f ) )
    {
        G_Dx11Renderer.SetLightDirection( Vector3( LightDirection[ 0 ], LightDirection[ 1 ], LightDirection[ 2 ] ) );
    }
}
