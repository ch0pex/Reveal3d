/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file transform.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "component.hpp"
#include "core/entity.hpp"

#include <set>
#include <vector>

namespace reveal3d::core {

class Transform : public Component<Transform> {
public:
  // *** Type Traits ***
  using pool_type = transform::Pool;
  using init_info = pool_type::init_info;

  using Component::Component;

  // *** Member getters ***

  // Todo this should be const reference
  [[nodiscard]] math::mat4& world() const { return pool().world(id_); }

  // Todo this should be const reference
  [[nodiscard]] math::mat4& invWorld() const { return pool().invWorld(id_); }

  [[nodiscard]] math::vec3 position() const { return pool().posRotScale(id_).position; }

  [[nodiscard]] math::vec3 scale() const { return pool().posRotScale(id_).scale; }

  [[nodiscard]] math::vec3 rotation() const { return math::vec_to_degrees(pool().posRotScale(id_).rotation); }

  [[nodiscard]] math::vec3 worldPosition() const {
    math::mat4 const world_mat = pool().world(id_);
    return translation(world_mat);
  }

  [[nodiscard]] math::vec3 worldScale() const { return math::scale(pool().world(id_)); }

  [[nodiscard]] math::vec3 worldRotation() const { return vec_to_degrees(math::rotation(pool().world(id_))); }

  // *** Member setters ***

  void position(math::vec3 const pos) const {
    pool().posRotScale(id_).position = pos;
    setDirty();
  }

  void scale(math::vec3 const size) const {
    pool().posRotScale(id_).scale = size;
    setDirty();
  }

  void rotation(math::vec3 const rot) const {
    pool().posRotScale(id_).rotation = vec_to_radians(rot);
    setDirty();
  }

  void worldPosition(math::vec3 const new_position) const {
    auto& [position, rotation, scale] = pool().posRotScale(id_);
    pool().world(id_)                 = transpose(affine_transformation(new_position, scale, rotation));
    if (auto const parent = entity().parent(); parent.isAlive()) {
      position = math::vec3 {transpose(parent.component<Transform>().invWorld()) * math::vec4 {new_position}};
    }
    else {
      position = new_position;
    }

    pool().invWorld(id_) = inverse(pool().world(id_));
    softDirty();
  }

  void worldScale(math::vec3 const new_scale) const {
    auto& [position, rotation, scale] = pool().posRotScale(id_);
    pool().world(id_)                 = transpose(affine_transformation(position, new_scale, rotation));
    if (Entity const parent = entity().parent(); parent.isAlive()) {
      scale = math::vec3 {parent.component<Transform>().invWorld() * math::vec4 {new_scale}};
    }
    else {
      scale = new_scale;
    }
    pool().invWorld(id_) = inverse(pool().world(id_));
    softDirty();
  }

  void worldRotation(math::vec3 const new_rot) const {
    auto& [position, rotation, scale] = pool().posRotScale(id_);

    auto const rad = vec_to_radians(new_rot);
    world()        = transpose(affine_transformation(position, scale, rad));
    if (Entity const parent = entity().parent(); parent.isAlive()) {
      rotation = math::vec3 {parent.component<Transform>().invWorld() * math::vec4 {rad}};
    }
    else {
      rotation = rad;
    }
    pool().invWorld(id_) = inverse(pool().world(id_));
    softDirty();
  }

  // *** Updating

  void update() const {
    if (pool().dirties().at(id::index(id_)) != 4) {
      return;
    }

    if (Entity const curr_node = entity(); curr_node.parent().isAlive()) {
      id_t const parent_id = curr_node.parent().id();
      curr_node.parent().component<Transform>().update();
      math::mat4 const parent_world = pool().world(parent_id);
      world()                       = parent_world * calcWorld(id_);
    }
    else {
      world() = calcWorld(id_);
    }
    invWorld() = transpose(inverse(world()));
    --pool().dirties().at(id::index(id_));
  }

  void unDirty() const {
    if (id_t const idx = id::index(id_); pool().dirties().at(idx) != 0) {
      --pool().dirties().at(idx);
    }
    else {
      pool().dirties().at(idx) = 0;
    }
  }

  void setDirty() const {
    if (dirty() == 4) {
      return;
    }
    if (dirty() == 0) {
      pool().dirtyIds().insert(id_);
    }
    setChildrenAsDirty();
    pool().dirties().at(id::index(id_)) = 4;
  }

  [[nodiscard]] u8 dirty() const { return pool().dirties().at(id::index(id_)); }

private:
  [[nodiscard]] auto calcWorld(id_t const id) const -> math::mat4 {
    auto& [position, rotation, scale] = scene_->pool<Transform>().posRotScale(id);
    return transpose(affine_transformation(position, scale, rotation));
  };

  void softDirty() const {
    pool().dirties().at(id::index(id_)) = 3;
    pool().dirtyIds().insert(id_);
    setChildrenAsDirty();
  }

  void setChildrenAsDirty() const {

    for (auto const children = entity().children(); auto const child: children) {
      child.component<Transform>().setDirty();
      child.component<Transform>().setChildrenAsDirty();
    }
  }
};

static_assert(component<Transform>);

template<>
inline void GenericPool<Transform::pool_type>::update(Scene& scene) {
  for (auto it = this->dirty_ids_.begin(); it != this->dirty_ids_.end();) {
    Transform component {&scene, *it};
    component.update();
    if (this->dirties_.at(id::index(*it)) == 0) {
      it = this->dirty_ids_.erase(it);
    }
    else {
      ++it;
    }
  }
}

} // namespace reveal3d::core
