#pragma once


#include <d3d11.h>


#pragma comment ( lib, "d3d11.lib" )


class Dx11Device
{
private:
    IDXGISwapChain*      SwapChain;
    ID3D11Device*        Device;
    ID3D11DeviceContext* DeviceContext;

public:
    // Create
    bool Create( HWND hWnd );

    // GetSwapChain
    IDXGISwapChain* GetSwapchain() const { return SwapChain; };

    // GetDevice
    ID3D11Device* GetDevice() const { return Device; };

    // GetDeviceContext
    ID3D11DeviceContext* GetDeviceContext() const { return DeviceContext; };
};


extern Dx11Device G_Dx11Device;


IDXGISwapChain* GetSwapChain();
ID3D11Device* GetDx11Device();
ID3D11DeviceContext* GetDx11DeviceContext();
