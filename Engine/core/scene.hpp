/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file scene.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "transform.hpp"
#include "geometry.hpp"
#include "script.hpp"
#include "common/timer.hpp"
#include "content/primitives.hpp"

#include <vector>

namespace reveal3d::core {

struct EntityInfo {
    Transform transform;
    Geometry geometry;
};

//TODO: ids, generation and custom std::vector
class Scene {
public:
    Scene() = default;
    ~Scene();

    Entity AddEntity(math::vec3 pos);
    Entity AddEntity(EntityInfo &entity);
    Entity AddPrimitive(Geometry::primitive type);
    Entity AddEntityFromObj(const wchar_t *path);

    INLINE std::string &GetName(u32 id) { return names_.at(id); }
    INLINE Transform &GetTransform(u32 id) { return transforms_.at(id); }
    INLINE Geometry &GetGeometry(u32 id) { return geometries_.at(id); }
    INLINE Script *GetScript(u32 id) { return scripts_.at(id); }

    [[nodiscard]] INLINE u32 NumEntities() const { return entities_; }
    INLINE std::vector<Transform>& Transforms() { return transforms_; }
    INLINE std::vector<Geometry>& Geometries() { return geometries_; }
    INLINE Entity GetEntity(u32 id);

    void Init();
    void Update(f32 dt);
    void AddScript(Script *script, u32 id);

private:
//    std::vector<u8> generations_;
//    std::vector<u8> freeIds_;
    std::vector<std::string> names_;
    std::vector<Transform> transforms_;
    std::vector<Geometry> geometries_;
    std::vector<Script *> scripts_;
    u32 entities_ { 0 };
//    std::vector<Light> lights;
};

extern Scene scene;

}
