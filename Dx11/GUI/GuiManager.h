#pragma once


#include "DevTestUI.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <d3d11.h>


//=====================================================================================================================
// @brief	GuiManager
//=====================================================================================================================
class GuiManager
{
private:
    DevTestUI DevTestUI;

public:
    // Constructor
    GuiManager() = default;

    // Destructor
    ~GuiManager() = default;

    // Initialize
    bool Initialize( HWND hWnd ) const;

    // PreRender
    void PreRender();

    // PostRender
    void PostRender() const;

    // Window message processor
    bool WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) const;

    // Get dev test ui
    class DevTestUI& GetDevTestUI() { return DevTestUI; }
};

//=====================================================================================================================
// @brief	GetGuiManager
//=====================================================================================================================
GuiManager* GetGuiManager();