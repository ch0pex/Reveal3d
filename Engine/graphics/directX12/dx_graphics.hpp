/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file dx_graphics.hpp
 * @version 1.0
 * @date 25/02/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include "dx_common.hpp"
#include "render/camera.hpp"
#include "window/window_info.hpp"

#include <array>

namespace reveal3d::graphics::Dx {

class Graphics {
public:
    explicit Graphics(const window::Resolution &res);
    void LoadPipeline();
    void LoadAssets();
    void Update(render::Camera &camera);
    void PopulateCommands();
    void Draw();
    void MoveToNextFrame();
    void Terminate();
    INLINE void SetWindow(WHandle winHandle) { window_ = winHandle; }
    [[nodiscard]] INLINE u32 GetWidth() const { return res.width; }
    [[nodiscard]] INLINE u32 GetHeight() const { return res.height; }


private:
    void InitDXGIAdapter();
    void CreateCommandQueue();
    void CreateSwapChain();
    void InitFrameResources();
    void InitFence();
    void WaitForGPU();


    /****************** Device Resources ******************/
    static const u32 bufferCount_ = 3;

    //D3D12_VIEWPORT viewport_;
    //D3D12_RECT scissorRect_;
    ComPtr<IDXGIFactory5> factory_;
    ComPtr<ID3D12Device> device_;
    ComPtr<ID3D12CommandQueue> commandQueue_;
    ComPtr<ID3D12GraphicsCommandList> commandList_;
    ComPtr<ID3D12CommandAllocator> commandAllocators_[bufferCount_];
    ComPtr<ID3D12Resource> renderTargets_[bufferCount_];
    ComPtr<IDXGISwapChain3> swapChain_;
    ComPtr<ID3D12DescriptorHeap> rtvHeap_;
    u32 rtvDescriptorSize_;
    //ComPtr<ID3D12RootSignature> rootSignature_;
    //ComPtr<ID3D12PipelineState> pipelineState_;

    // App resources.
    //ComPtr<ID3D12Resource> vertexBuffer_;
    //D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

    // Synchronization objects.
    u8 frameIndex_;
    HANDLE fenceEvent_;
    ComPtr<ID3D12Fence> fence_;
    u64 fenceValues_[bufferCount_];
    /********************************************************/

    window::Resolution res;
    HWND window_;
};

}

using reveal3d::graphics::Dx::Graphics;