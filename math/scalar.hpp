/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file concepts.hpp
 * @version 1.0
 * @date 3/6/2025
 * @brief  Math module concepts
 *
 */

#pragma once

#include <concepts>

namespace reveal3d::math {

template<typename T>
concept scalar = std::integral<T> || std::floating_point<T>;

}
