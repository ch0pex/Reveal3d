/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file dx_common.hpp
 * @version 1.0
 * @date 27/02/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "common/common.hpp"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include "d3dx12.h"

#include "dx_utils.hpp"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

namespace reveal3d::graphics::dx12 {

constexpr u32 frameBufferCount = 3;

}

