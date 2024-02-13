/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file window_info.hpp
 * @version 1.0
 * @date 09/03/2024
 * @brief Short description
 *
 * Window initialization info
 */

#pragma once

#include "common/common.hpp"

namespace reveal3d::window {

struct Resolution {
    Resolution(u32 width, u32 height) :
        width(width), height(height) ,
        aspectRatio(static_cast<f32>(width) / static_cast<f32>(height)) {}
    u32 width;
    u32 height;
    f32 aspectRatio;
};

struct InitInfo {
    WHandle windowHandle { nullptr };
    WCallback callback { nullptr }; // Unused for now, usefull in a future
    const wchar_t * name { nullptr };
    Resolution res { 1920, 1080 };
};

}

