/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file concepts.hpp
 * @version 1.0
 * @date 3/6/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "matrix.hpp"
#include "vector.hpp"

namespace reveal3d::math {

namespace detail {

template<scalar T>
struct is_vector : std::false_type { };

template<scalar T>
struct is_vector<Vec2<T>> : std::true_type { };

template<scalar T>
struct is_vector<Vec3<T>> : std::true_type { };

template<scalar T>
struct is_vector<Vec4<T>> : std::true_type { };

template<scalar T>
struct is_matrix : std::false_type { };

template<scalar T>
struct is_matrix<Mat3x3<T>> : std::true_type { };

template<scalar T>
struct is_matrix<Mat4x4<T>> : std::true_type { };
} // namespace detail

template<typename T>
concept vector = detail::is_vector<T>::value;

template<typename T>
concept matrix = detail::is_matrix<T>::value;

template<typename T>
concept algebra_type = detail::is_vector<T>::value or detail::is_matrix<T>::value;

} // namespace reveal3d::math
