/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file functions.hpp
 * @version 1.0
 * @date 01/03/2024
 * @brief Math functiosn
 *
 * Math inline template functions for vector, scalar and matrix
 */

#pragma once

#include <concepts>
#include <glm/gtc/matrix_transform.hpp>

namespace reveal3d::math {

INLINE scalar Cos(scalar s) {return glm::radians(s); }
INLINE scalar Sin(scalar s) {return glm::radians(s); }
INLINE scalar Radians(scalar s) {return glm::radians(s); }
INLINE xvec3 Normalize(xvec3 v) { return glm::normalize(glm::vec3(v)); }
INLINE xvec3 Normalize(xvec4 v) { return glm::normalize(glm::vec3(v)); }
INLINE xvec3 Cross(xvec3 v1, xvec3 v2) { return glm::cross(glm::vec3(v1), glm::vec3(v2)); }
INLINE xvec3 VecToRadians(xvec3 v) { return { glm::radians(v.GetX()), glm::radians(v.GetY()), glm::radians(v.GetZ()) }; }
INLINE xvec3 VecToDegrees(xvec3 v) { return { glm::degrees(v.GetX()), glm::degrees(v.GetY()), glm::degrees(v.GetZ()) }; }
INLINE mat4 Transpose(mat4 mat) { return glm::transpose(glm::mat4(mat)); }
INLINE mat4 LookAt(xvec3 position, xvec3 focusPoint, xvec3 upDir) { return glm::lookAt(glm::vec3(position), glm::vec3(focusPoint), glm::vec3(upDir)); }
INLINE mat4 PerspectiveFov(f32 fov, f32 aspectRatio, f32 nearPlane, f32 farPlane) { return glm::perspective(fov, aspectRatio, nearPlane, farPlane); }
INLINE mat4 AffineTransformation(const xvec3 position, const xvec3 scale, const xvec3 rotation) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.GetX(), glm::vec3(1.0f, 0.0f, 0.0f)) *
                               glm::rotate(glm::mat4(1.0f), rotation.GetY(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                               glm::rotate(glm::mat4(1.0f), rotation.GetZ(), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));

    return translationMatrix * rotationMatrix * scaleMatrix;
}

}
