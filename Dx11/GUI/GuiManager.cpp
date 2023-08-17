#include "GuiManager.h"
#include "imgui_internal.h"
#include "../Core/Dx11Device.h"


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


GuiManager G_GuiManager;

GuiManager* GetGuiManager() { return &G_GuiManager; }


//=================================================================================================
// @brief	Initialize
//=================================================================================================
bool GuiManager::Initialize( HWND hWnd ) const
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init( hWnd );
    ImGui_ImplDX11_Init( GetDx11Device(), GetDx11DeviceContext() );

    return true;
}

//=================================================================================================
// @brief	PreRender
//=================================================================================================
void GuiManager::PreRender()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    DevTestUI.Render();
}

//=================================================================================================
// @brief	PostRender
//=================================================================================================
void GuiManager::PostRender() const
{
    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
}

//=================================================================================================
// @brief	Window message processor
//=================================================================================================
bool GuiManager::WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) const
{
    if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) )
        return true;

    return false;
}
