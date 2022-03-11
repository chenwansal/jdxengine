#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height) {
    if (!InitializeDirectX(hwnd, width, height)) {
        PLogger::ConsoleLog("false");
        return false;
    }
    return true;
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height) {

    // DEVICE AND SWAPCHAIN
    vector<GraphicAdapterData> adapters =
        GraphicAdapterReader::GetAdapterDatas();

    if (adapters.size() < 1) {
        PLogger::PopupError("NO IDXGI ADAPTER");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HRESULT hr;
    hr = D3D11CreateDeviceAndSwapChain(
        adapters[0].ptrAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, NULL, NULL, 0,
        D3D11_SDK_VERSION, &scd, this->ptrSwapchain.GetAddressOf(),
        this->ptrDevice.GetAddressOf(), NULL,
        this->ptrDeviceContext.GetAddressOf());

    if (FAILED(hr)) {
        PLogger::PopupErrorWithResult(hr,
                                      "FAILED CREATE DEVICE AND SWAP CHAIN");
        return false;
    }

    ComPtr<ID3D11Texture2D> backBuffer;
    hr = this->ptrSwapchain->GetBuffer(
        0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void **>(backBuffer.GetAddressOf()));

    if (FAILED(hr)) {
        PLogger::PopupErrorWithResult(hr, "GETBUFFER FAILED");
        return false;
    }

    // RENDER TARGET VIEW
    hr = this->ptrDevice->CreateRenderTargetView(
        backBuffer.Get(), NULL, this->ptrRenderTargetView.GetAddressOf());

    if (FAILED(hr)) {
        PLogger::PopupErrorWithResult(hr, "CERATE RENDER TARGET");
        return false;
    }

    this->ptrDeviceContext->OMSetRenderTargets(
        1, this->ptrRenderTargetView.GetAddressOf(), NULL);

    return true;
}

void Graphics::RenderFrame() {
    float bgcolor[] = {0.0f, 0.0f, 1.0f, 1.0f};
    this->ptrDeviceContext->ClearRenderTargetView(
        this->ptrRenderTargetView.Get(), bgcolor);
    this->ptrSwapchain->Present(1, NULL);
}