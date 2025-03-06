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

namespace reveal3d::math::detail {

// clang-format off

template<typename T>
struct Mat3x3  {
  constexpr Mat3x3() : x {}, y {}, z {} { }

  constexpr Mat3x3(T x, T y, T z) : x {x}, y {y}, z {z} { }

  constexpr Mat3x3 operator-() const { return {-x, -y, -z}; }

  constexpr Mat3x3 operator+() const { return {+x, +y, +z}; }

  constexpr Mat3x3 operator+=(Mat3x3 const& m2) const { x += m2.x, y += m2.y, z += m2.z; return *this; }

  constexpr Mat3x3 operator-=(Mat3x3 const& m2) const { x -= m2.x, y -= m2.y, z -= m2.z; return *this; }

  // constexpr Mat3x3 operator*=(Mat3x3 const m2) const { x *= m2.x, y *= m2.y, z *= m2.z; return *this; }

  // constexpr Mat3x3 operator/=(Mat3x3 const m2) const { x /= m2.x, y /= m2.y, z /= m2.z; return *this; }

  Vec3<T> x, y, z;
};

template<typename T>
struct Mat4x4 {
  constexpr Mat4x4() : x {}, y {}, z {}, w {} { }

  constexpr Mat4x4(Vec4<T> const x, Vec4<T> const y, Vec4<T> const z, Vec4<T> const w) : x {x}, y {y}, z {z}, w {w} { }

  constexpr Mat4x4(Mat3x3<T> xyz, T w) : x {xyz.x}, y {xyz.y}, z {xyz.z}, w {w} { }

  constexpr Mat4x4 operator-() const { return {-x, -y, -z, -w}; }

  constexpr Mat4x4 operator+() const { return {+x, +y, +z, +w}; }

  constexpr Mat4x4 operator+=(Mat4x4 const& m2) const { x += m2.x, y += m2.y, z += m2.z, w += m2.w; return *this; }

  constexpr Mat4x4 operator-=(Mat4x4 const& m2) const { x -= m2.x, y -= m2.y, z -= m2.z, w -= m2.w; return *this; }

  // constexpr Mat4x4 operator*=(Mat4x4 const& m2) const { x *= m2.x, y *= m2.y, z *= m2.z, w *= m2.w; return *this; }

  // constexpr Mat4x4 operator/=(Mat4x4 const& m2) const { x /= m2.x, y /= m2.y, z /= m2.z,  w /= m2.w; return *this; }

  T x, y, z, w;
};

// clang-format on

using mat3 = Mat3x3<f32>;
using mat4 = Mat4x4<f32>;


} // namespace reveal3d::math::detail
