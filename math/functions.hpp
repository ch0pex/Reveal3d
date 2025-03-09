/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file functions.hpp
 * @version 1.0
 * @date 01/03/2024
 * @brief Math functions
 *
 * Math inline template functions for vector, scalar and matrix
 */
#pragma once

#include "concepts.hpp"


namespace reveal3d::math {

// clang-format off

template<scalar T>
constexpr T determinant(Mat3x3<T> const& m) {
  return (m.x.x * (m.y.y * m.z.z - m.y.z * m.z.y)) -
         (m.x.y * (m.y.x * m.z.z - m.y.z * m.z.x)) +
         (m.x.z * (m.y.x * m.z.y - m.y.y * m.z.x));
}

template<scalar T>
constexpr Mat3x3<T> adjugate(Mat3x3<T> const& m) {
  return {
      {(m.y.y * m.z.z) - (m.y.z * m.z.y), (m.x.z * m.z.y) - (m.x.y * m.z.z), (m.x.y * m.y.z) - (m.x.z * m.y.y)},
      {(m.y.z * m.z.x) - (m.y.x * m.z.z), (m.x.x * m.z.z) - (m.x.z * m.z.x), (m.x.z * m.y.x) - (m.x.x * m.y.z)},
      {(m.y.x * m.z.y) - (m.y.y * m.z.x), (m.x.y * m.z.x) - (m.x.x * m.z.y), (m.x.x * m.y.y) - (m.x.y * m.y.x)}
  };
}

template <scalar T>
constexpr T determinant(Mat4x4<T> const& m) {
    // Determinantes de las submatrices 3x3 (menores)
    T det0 = determinant(Mat3x3<T>{ {m.y.y, m.y.z, m.y.w}, {m.z.y, m.z.z, m.z.w}, {m.w.y, m.w.z, m.w.w} });
    T det1 = determinant(Mat3x3<T>{ {m.y.x, m.y.z, m.y.w}, {m.z.x, m.z.z, m.z.w}, {m.w.x, m.w.z, m.w.w} });
    T det2 = determinant(Mat3x3<T>{ {m.y.x, m.y.y, m.y.w}, {m.z.x, m.z.y, m.z.w}, {m.w.x, m.w.y, m.w.w} });
    T det3 = determinant(Mat3x3<T>{ {m.y.x, m.y.y, m.y.z}, {m.z.x, m.z.y, m.z.z}, {m.w.x, m.w.y, m.w.z} });

    return (m.x.x * det0) - (m.x.y * det1) + (m.x.z * det2) - (m.x.w * det3);
}

template <scalar T>
constexpr Mat4x4<T> adjugate(Mat4x4<T> const& m) {
    return {
        {
            determinant(Mat3x3<T>{ {m.y.y, m.y.z, m.y.w}, {m.z.y, m.z.z, m.z.w}, {m.w.y, m.w.z, m.w.w} }),
            -determinant(Mat3x3<T>{ {m.x.y, m.x.z, m.x.w}, {m.z.y, m.z.z, m.z.w}, {m.w.y, m.w.z, m.w.w} }),
            determinant(Mat3x3<T>{ {m.x.y, m.x.z, m.x.w}, {m.y.y, m.y.z, m.y.w}, {m.w.y, m.w.z, m.w.w} }),
            -determinant(Mat3x3<T>{ {m.x.y, m.x.z, m.x.w}, {m.y.y, m.y.z, m.y.w}, {m.z.y, m.z.z, m.z.w} })
        },
        {
            -determinant(Mat3x3<T>{ {m.y.x, m.y.z, m.y.w}, {m.z.x, m.z.z, m.z.w}, {m.w.x, m.w.z, m.w.w} }),
            determinant(Mat3x3<T>{ {m.x.x, m.x.z, m.x.w}, {m.z.x, m.z.z, m.z.w}, {m.w.x, m.w.z, m.w.w} }),
            -determinant(Mat3x3<T>{ {m.x.x, m.x.z, m.x.w}, {m.y.x, m.y.z, m.y.w}, {m.w.x, m.w.z, m.w.w} }),
            determinant(Mat3x3<T>{ {m.x.x, m.x.z, m.x.w}, {m.y.x, m.y.z, m.y.w}, {m.z.x, m.z.z, m.z.w} })
        },
        {
            determinant(Mat3x3<T>{ {m.y.x, m.y.y, m.y.w}, {m.z.x, m.z.y, m.z.w}, {m.w.x, m.w.y, m.w.w} }),
            -determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.w}, {m.z.x, m.z.y, m.z.w}, {m.w.x, m.w.y, m.w.w} }),
            determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.w}, {m.y.x, m.y.y, m.y.w}, {m.w.x, m.w.y, m.w.w} }),
            -determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.w}, {m.y.x, m.y.y, m.y.w}, {m.z.x, m.z.y, m.z.w} })
        },
        {
            -determinant(Mat3x3<T>{ {m.y.x, m.y.y, m.y.z}, {m.z.x, m.z.y, m.z.z}, {m.w.x, m.w.y, m.w.z} }),
            determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.z}, {m.z.x, m.z.y, m.z.z}, {m.w.x, m.w.y, m.w.z} }),
            -determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.z}, {m.y.x, m.y.y, m.y.z}, {m.w.x, m.w.y, m.w.z} }),
            determinant(Mat3x3<T>{ {m.x.x, m.x.y, m.x.z}, {m.y.x, m.y.y, m.y.z}, {m.z.x, m.z.y, m.z.z} })
        }
    };
}

template<matrix T>
constexpr T inverse(T const& m) {
  auto det = determinant(m);
  if (det == 0) {
    return {};
  }
  return adjugate(m) * (1 / det);
}

template<scalar T>
constexpr Mat3x3<T> transpose(Mat3x3<T> const& m) {
  return {
      {m.x.x, m.y.x, m.z.x},
      {m.x.y, m.y.y, m.z.y},
      {m.x.z, m.y.z, m.z.z}
  };
}

template<typename T>
constexpr Mat4x4<T> transpose(Mat4x4<T> const& m) {
  return {
      {m.x.x, m.y.x, m.z.x, m.w.x},
      {m.x.y, m.y.y, m.z.y, m.w.y},
      {m.x.z, m.y.z, m.z.z, m.w.z},
      {m.x.w, m.y.w, m.z.w, m.w.w}
  };
}

template<scalar T>
T dot(Vec2<T> const vec, Vec2<T> const other) {
  auto mul = vec * other;
  return mul.x + mul.y;
}

template<scalar T>
T dot(Vec3<T> const vec, Vec3<T> const other) {
  auto mul = vec * other;
  return mul.x + mul.y + mul.z;
}

template<scalar T>
T dot(Vec4<T> const vec, Vec4<T> const other) {
  auto mul = vec * other;
  return mul.x + mul.y + mul.z + mul.w;
}

template<scalar T>
constexpr auto cross(Vec3<T> const& vec1, Vec3<T> const& vec2) -> Vec3<T> {
  return {
    (vec1.y * vec2.z) - (vec1.z * vec2.y),
    (vec1.z * vec2.x) - (vec1.x * vec2.z),
    (vec1.x * vec2.y) - (vec1.y * vec2.x)
  };
}

template<scalar T> T cos(T s) { return std::cosf(static_cast<f32>(s)); }

template<scalar T> T sin(T s) { return std::sinf(static_cast<f32>(s)); }

template<scalar T> T tan(T s) { return std::tanf(static_cast<f32>(s)); }

template<scalar T>
Mat4x4<T> affine_transformation(Vec3<T> const position, Vec3<T> const scale, Vec3<T> const rotation) {
  // TODO
  return {};
}

template<std::floating_point T>
Mat4x4<T> perspective_fov(T const fov, T const aspect_ratio, T const near_plane, T const far_plane) {
  // TODO
  return {};
}

template<scalar T>
Mat4x4<T> look_at(Vec3<T> const position, Vec3<T> const scale, Vec3<T> const rotation) {
 // TODO
  return {};
}

inline f32 fast_inverse_square(f32 x) {
    i64 i = *reinterpret_cast<i64*>(&x);
    i = 0x5f3759df - (i >> 1);
    x = *reinterpret_cast<f32*>(&i);
    x = x * (1.5F - 0.5F * x * x);
    return x;
}

template<std::floating_point T>
Vec3<T> normalize(Vec3<T> const& v) {
    f32 const magSquared = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    f32 invSqrt = fast_inverse_square(magSquared);

    return {v.x * invSqrt, v.y * invSqrt, v.z * invSqrt};
}

template<scalar T>
constexpr auto degrees(T const radians) -> T {
  //TODO
  return {};
}

template<scalar T>
constexpr auto radians(T const degrees) -> T {
  return degrees * (std::numbers::pi_v<T> / static_cast<T>(180));
}

template<scalar T>
constexpr auto vec_to_radians(Vec3<T> vec3) -> Vec3<T> {
  return {radians(vec3.x), radians(vec3.y), radians(vec3.z)};
}

template<scalar T>
constexpr auto vec_to_radians(Vec4<T> vec4) -> Vec4<T> {
  return {radians(vec4.x), radians(vec4.y), radians(vec4.z), radians(vec4.w)};
}

template<scalar T>
constexpr auto vec_to_degrees(Vec3<T> vec3) -> Vec3<T> {
  return {degrees(vec3.x), degrees(vec3.y), degrees(vec3.z)};
}

template<scalar T>
constexpr auto vec_to_degrees(Vec4<T> vec4) -> Vec4<T> {
  return {degrees(vec4.x), degrees(vec4.y), degrees(vec4.z), degrees(vec4.w)};
}

template<scalar T>
constexpr auto translation(Mat4x4<T>) -> Vec3<T> {
  // TODO
  return {};
}

template<scalar T>
constexpr auto scale(Mat4x4<T>) -> Vec3<T> {
  // TODO
  return {};
}

template<scalar T>
constexpr auto rotation(Mat4x4<T>) -> Vec3<T> {
  // TODO
  return {};
}

// clang-format on

} // namespace reveal3d::math
