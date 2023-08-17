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
}
