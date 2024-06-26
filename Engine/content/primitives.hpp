/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file primitives.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#include "core/geometry.hpp"

namespace reveal3d::content {

u16 GetCubeData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);
u16 GetPlaneData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);
u16 GetSphereData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);
u16 GetCylinderData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);
u16 GetConeData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);
u16 GetTorusData(std::vector<render::Vertex> &vertices, std::vector<u32> &indices, u16 offset = 0);

}

