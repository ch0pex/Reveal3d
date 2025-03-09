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

#include "vector.hpp"
#include "matrix.hpp"
#include "concepts.hpp"

namespace reveal3d::math {

// clang-format off

template<algebra_type T> auto operator+(T lh, T const rh) { lh += rh; return lh; }

template<algebra_type T> auto operator-(T lh, T const rh) { lh -= rh; return lh; }

template<algebra_type T> auto operator*(T lh, T const rh) { lh *= rh; return lh; }

template<algebra_type T> auto operator/(T lh, T const rh) { lh /= rh; return lh; }

auto operator+(algebra_type auto lh, scalar auto const rh) { lh += rh; return lh; }

auto operator-(algebra_type auto lh, scalar auto const rh) { lh -= rh; return lh; }

auto operator*(algebra_type auto lh, scalar auto const rh) { lh *= rh; return lh; }

auto operator/(algebra_type auto lh, scalar auto const rh) { lh /= rh; return lh; }

auto operator+(scalar auto const lh, algebra_type auto rh) { rh += lh; return rh; }

auto operator-(scalar auto const lh, algebra_type auto rh) { rh -= lh; return rh; }

auto operator*(scalar auto const lh, algebra_type auto rh) { rh *= lh; return rh; }

auto operator/(scalar auto const lh, algebra_type auto rh) { rh /= lh; return rh; }

template<scalar T>
auto operator*(Mat3x3<T> const& mat3, Vec3<T> const vec3) -> Vec3<T> {
   return {mat3.x * vec3, mat3.y * vec3, mat3.z * vec3};
}

template<scalar T>
auto operator/(Mat3x3<T> const& mat3, Vec3<T> const vec3) -> Vec3<T> {
   return {dot(mat3.x, vec3), dot(mat3.y, vec3), dot(mat3.z, vec3)};
}

template<scalar T>
auto operator*(Mat4x4<T> const& mat4, Vec4<T> const vec4) -> Vec4<T> {
   return {dot(mat4.x, vec4), dot(mat4.y, vec4), dot(mat4.z, vec4), dot(mat4.w, vec4)};
}

template<scalar T>
auto operator/(Mat4x4<T> const& mat4, Vec4<T> const vec4) -> Vec4<T> {
   return {mat4.x / vec4, mat4.y / vec4, mat4.z / vec4, mat4.w / vec4};
}

/*
template<vector T> T operator+(T lh, T const rh) { lh += rh; return lh; }

template<vector T> T operator-(T lh, T const rh) { lh -= rh; return lh; }

template<vector T> T operator*(T lh, T const rh) { lh *= rh; return lh; }

template<vector T> T operator/(T lh, T const rh) { lh /= rh; return lh; }

template<matrix T> T operator+(T lh, T const& rh) { lh += rh; return lh; }

template<matrix T> T operator-(T lh, T const& rh) { lh -= rh; return lh; }

template<matrix T> T operator*(T lh, T const& rh) { lh *= rh; return lh; }

template<matrix T> T operator/(T lh, T const& rh) { lh /= rh; return lh; }

template<vector T> T operator+(T lh, scalar auto const rh) { lh += rh; return lh; }

template<vector T> T operator-(T lh, scalar auto const rh) { lh -= rh; return lh; }

template<vector T> T operator*(T lh, scalar auto const rh) { lh *= rh; return lh; }

template<vector T> T operator/(T lh, scalar auto const rh) { lh /= rh; return lh; }

template<matrix T> T operator+(T lh, scalar auto const rh) { lh += rh; return lh; }

template<matrix T> T operator-(T lh, scalar auto const rh) { lh -= rh; return lh; }

template<matrix T> T operator*(T lh, scalar auto const rh) { lh *= rh; return lh; }

template<matrix T> T operator/(T lh, scalar auto const rh) { lh /= rh; return lh; }

template<vector T> T operator+(scalar auto lh, T const rh) { rh += lh; return rh; }

template<vector T> T operator-(scalar auto lh, T const rh) { rh -= lh; return rh; }

template<vector T> T operator*(scalar auto lh, T const rh) { rh *= lh; return rh; }

template<vector T> T operator/(scalar auto lh, T const rh) { rh /= lh; return rh; }

template<matrix T> T operator+(scalar auto lh, T const& rh) { rh += lh; return rh; }

template<matrix T> T operator-(scalar auto lh, T const& rh) { rh -= lh; return rh; }

template<matrix T> T operator*(scalar auto lh, T const& rh) { rh *= lh; return rh; }

template<matrix T> T operator/(scalar auto lh, T const& rh) { rh /= lh; return rh; }
*/

// clang-format on

} // namespace reveal3d::math
