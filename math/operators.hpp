/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file utils.hpp
 * @version 1.0
 * @date 03/02/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "concepts.hpp"

namespace reveal3d::math {

// clang-format off

template<vector T> T operator+(T lh, T const rh) { lh += rh; return lh; }

template<vector T> T operator-(T lh, T const rh) { lh -= rh; return lh; }

template<vector T> T operator*(T lh, T const rh) { lh *= rh; return lh; }

template<vector T> T operator/(T lh, T const rh) { lh /= rh; return lh; }

template<matrix T> T operator+(T lh, T const& rh) { lh += rh; return lh; }

template<matrix T> T operator-(T lh, T const& rh) { lh -= rh; return lh; }

template<matrix T> T operator*(T lh, T const& rh) { lh *= rh; return lh; }

template<matrix T> T operator/(T lh, T const& rh) { lh /= rh; return lh; }

// clang-format on

} // namespace reveal3d::math
