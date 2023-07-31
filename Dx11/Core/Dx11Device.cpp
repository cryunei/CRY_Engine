#include "Dx11Device.h"


Dx11Device G_Dx11Device;


//=================================================================================================
// @brief	Create
//=================================================================================================
bool Dx11Device::Create( HWND hWnd )
{
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory( &scd, sizeof( DXGI_SWAP_CHAIN_DESC ) );

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = true;

    HRESULT hr = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, SwapChainComPtr.GetAddressOf(), DeviceComPtr.GetAddressOf(), nullptr, DeviceContextComPtr.GetAddressOf() );
    if ( FAILED( hr ) ) return false;
        
    return true;
}

IDXGISwapChain* GetSwapChain() { return G_Dx11Device.GetSwapchain(); }
ID3D11Device* GetDx11Device() { return G_Dx11Device.GetDevice(); }
ID3D11DeviceContext* GetDx11DeviceContext() { return G_Dx11Device.GetDeviceContext(); }
