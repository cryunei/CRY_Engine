#pragma once


#include "../DxCoreInc.h"


class Dx11Device
{
private:
    ComPtr< IDXGISwapChain > SwapChainComPtr;
    ComPtr< ID3D11Device >   DeviceComPtr;
    ComPtr< ID3D11DeviceContext > DeviceContextComPtr;

public:
    // Create
    bool Create( HWND hWnd );

    // GetSwapChain
    IDXGISwapChain* GetSwapchain() const { return SwapChainComPtr.Get(); };

    // GetDevice
    ID3D11Device* GetDevice() const { return DeviceComPtr.Get(); };

    // GetDeviceContext
    ID3D11DeviceContext* GetDeviceContext() const { return DeviceContextComPtr.Get(); };
};


extern Dx11Device G_Dx11Device;


IDXGISwapChain* GetSwapChain();
ID3D11Device* GetDx11Device();
ID3D11DeviceContext* GetDx11DeviceContext();
