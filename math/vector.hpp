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

#include "common/common.hpp"
#include "scalar.hpp"

namespace reveal3d::math {

// clang-format off

template<scalar T> struct Vec2;

template<scalar T> struct Vec3;

template<scalar T> struct Vec4;

template<scalar T>
struct Vec2 {
  constexpr Vec2() : x {}, y {} { }

  constexpr Vec2(T const x, T y) : x {x}, y {y} { }

  constexpr Vec2 operator-() const { return {-x, -y}; }

  constexpr Vec2 operator+() const { return {+x, +y}; }

  constexpr Vec2 operator+=(Vec2 const v2) const { x += v2.x, y += v2.y; return *this; }

  constexpr Vec2 operator-=(Vec2 const v2) const { x -= v2.x, y -= v2.y; return *this; }

  constexpr Vec2 operator*=(Vec2 const v2) const { x *= v2.x, y *= v2.y; return *this; }

  constexpr Vec2 operator/=(Vec2 const v2) const { x /= v2.x, y /= v2.y; return *this; }

  template<typename U> explicit constexpr operator Vec2<U>() const { return {x, y}; }

  T x, y;
};

template<typename T>
struct Vec3 {
  constexpr Vec3() : x {}, y {}, z {} { }

  constexpr Vec3(Vec2<T> const vec2, T z) : x {vec2.x}, y {vec2.y}, z {z} { }

  constexpr Vec3(T const x, T const y, T const z) : x {x}, y {y}, z {z} { }

  constexpr auto xy() const -> Vec2 { return {x, y}; }

  constexpr Vec3 operator-() const { return {-x, -y, -z}; }

  constexpr Vec3 operator+() const { return {+x, +y, +z}; }

  constexpr Vec3 operator+=(Vec3 const v2) const { x += v2.x, y += v2.y, z += v2.z; return *this; }

  constexpr Vec3 operator-=(Vec3 const v2) const { x -= v2.x, y -= v2.y, z -= v2.z; return *this; }

  constexpr Vec3 operator*=(Vec3 const v2) const { x *= v2.x, y *= v2.y, z *= v2.z; return *this; }

  constexpr Vec3 operator/=(Vec3 const v2) const { x /= v2.x, y /= v2.y, z /= v2.z; return *this; }

  template<scalar U> explicit constexpr operator Vec3<U>() const { return {x, y, z}; }

  T x, y, z;
};

template<scalar T>
struct Vec4 {
  constexpr Vec4() : x {}, y {}, z {}, w {} { }

  constexpr Vec4(Vec2<T> const xy, T const z, T const w) : x {xy.x}, y {xy.y}, z {z}, w {w} { }

  constexpr Vec4(Vec3<T> const xyz, T const w) : x {xyz.x}, y {xyz.y}, z {xyz.z}, w {w} { }

  constexpr Vec4(T const x, T const y, T const  z, T const w) : x {x}, y {y}, z {z}, w {w} { }

  constexpr Vec3<T> xyz() const { return {x, y, z, w}; }

  constexpr Vec4 operator-() const { return {-x, -y, -z, -w}; }

  constexpr Vec4 operator+() const { return {+x, +y, +z, +w}; }

  constexpr Vec4 operator+=(Vec4 const v2) const { x += v2.x, y += v2.y, z += v2.z, w += v2.w; return *this; }

  constexpr Vec4 operator-=(Vec4 const v2) const { x -= v2.x, y -= v2.y, z -= v2.z, w -= v2.w; return *this; }

  constexpr Vec4 operator*=(Vec4 const v2) const { x *= v2.x, y *= v2.y, z *= v2.z, w *= v2.w; return *this; }

  constexpr Vec4 operator/=(Vec4 const v2) const { x /= v2.x, y /= v2.y, z /= v2.z,  w /= v2.w; return *this; }

  template<scalar U> explicit constexpr operator Vec4<U>() const { return {x, y, z, w}; }

  T x, y, z, w;
};

// clang-format on

using vec2 = Vec2<f32>;
using vec3 = Vec3<f32>;
using vec4 = Vec4<f32>;


} // namespace reveal3d::math
