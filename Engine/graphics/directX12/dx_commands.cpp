/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file dx_commands.cpp
 * @version 1.0
 * @date 12/03/2024
 * @brief Commnads Manager 
 *
 * Commnads manager methods definition 
 * 
 */

#include "dx_commands.hpp"
#include "dx_utils.hpp"


namespace reveal3d::graphics::dx12 {

/**
 * @brief Current frame initialization
 */
u8 Commands::frameIndex_ = 0;

/**
 * @brief Commmands::Init
 * 
 * Create and Initializes the main commands and list queue 
 * It creates 3 commands allocators one for each final render target buffer 
 * 
 * @param[in] device GPU device ptr
 * 
 * @returns
 *  - None
 */
void Commands::Init(ID3D12Device *device) {
    const D3D12_COMMAND_QUEUE_DESC queueDesc {
            .Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
            .Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
            .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
            .NodeMask = 0
    };
    ResetFences();
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue_)) >> utl::DxCheck;

    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_)) >> utl::DxCheck;
    fenceEvent_ = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (fenceEvent_ == nullptr) {
        GetLastError() >> utl::DxCheck;
        throw std::runtime_error("Failed to create fence event");
    }

    for(auto & commandAllocator : commandAllocators_) {
        device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) >> utl::DxCheck;
    }

    device->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocators_[frameIndex_].Get(),
                               nullptr, IID_PPV_ARGS(&commandList_)) >> utl::DxCheck;
    commandList_->Close();
}

/**
 * @brief Commmands::Reset
 * 
 * Resets the current commnad allocator and 
 * the command list 
 * 
 * @note Use this when you want to start recording commands
 * 
 * @param[in] pso Pipeline state object 
 * 
 * @returns
 *  - None
 */
void Commands::Reset(ID3D12PipelineState *pso) {
    commandAllocators_[frameIndex_]->Reset() >> utl::DxCheck;
    commandList_->Reset(commandAllocators_[frameIndex_].Get(), pso) >> utl::DxCheck;
}

/**
 * @brief Commmands::WaitForGPU
 * 
 * Waits till the GPU has released the current frame resources 
 * 
 * @returns
 *  - None
 */
void Commands::WaitForGPU() {
    fenceValues_[frameIndex_]++;
    commandQueue_->Signal(fence_.Get(), fenceValues_[frameIndex_]) >> utl::DxCheck;
    auto lastCompleted = fence_->GetCompletedValue();
    if ( lastCompleted < fenceValues_[frameIndex_])
    {
        fence_->SetEventOnCompletion(fenceValues_[frameIndex_], fenceEvent_) >> utl::DxCheck;
        if (WaitForSingleObject(fenceEvent_, INFINITE) == WAIT_FAILED) {
            GetLastError() >> utl::DxCheck;
        }
    }
}

/**
 * @brief Commmands::MoveToNextFrame
 * 
 * Waits till the GPU has released the current frame resources 
 * and sets the frame index to the next 
 * 
 * @returns
 *  - None
 */
void Commands::MoveToNextFrame() {
    const u64 currentFenceVal = fenceValues_[frameIndex_];

    commandQueue_->Signal(fence_.Get(), currentFenceVal) >> utl::DxCheck;

    frameIndex_ = ++frameIndex_ % bufferCount_;

    if (fence_->GetCompletedValue() < fenceValues_[frameIndex_])
    {
        fence_->SetEventOnCompletion(fenceValues_[frameIndex_], fenceEvent_) >> utl::DxCheck;
        if (WaitForSingleObject(fenceEvent_, INFINITE) == WAIT_FAILED) {
            GetLastError() >> utl::DxCheck;
        }
    }

    fenceValues_[frameIndex_] = currentFenceVal + 1;
}

/**
 * @brief Commmands::Execute
 * 
 * Executes the recorded commands in the command list
 * 
 * @returns
 *  - None
 */
void Commands::Execute() {
    ID3D12CommandList* ppCommandLists[] = { commandList_.Get() };
    commandQueue_->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

/**
 * @brief Commmands::Execute
 * 
 * Executes the recorded commands in the command list
 * 
 * @returns
 *  - None
 */
void Commands::Flush() {
    WaitForGPU();
    CloseHandle(fenceEvent_);
}

/**
 * @brief Commmands::ResetFences
 * 
 * Reset all fences values to 0
 * 
 * @note This is only used to help out when resizing the screen 
 * 
 * @returns
 *  - None
 */
void Commands::ResetFences() {
    frameIndex_ = 0;
    fenceValues_[1] = 0;
    fenceValues_[2] = 0;
}

}