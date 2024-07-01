/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file dx_common.hpp
 * @version 1.0
 * @date 27/02/2024
 * @brief D3D12 common includes 
 *
 */

#pragma once

#include "common/common.hpp"
#include "d3dx12.h"
#include "dx_utils.hpp"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl.h>

#ifdef IMGUI
#include "IMGUI/imgui.h"
#include "IMGUI/backends/imgui_impl_dx12.h"
//#include "IMGUI/imgui_internal.h"
#endif

using namespace DirectX;
using Microsoft::WRL::ComPtr;

namespace reveal3d::graphics::dx12 {

constexpr u32 frameBufferCount = 3;

}

