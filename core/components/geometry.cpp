/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file geometry.cpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#include "geometry.hpp"

#include "content/primitives.hpp"
#include "core/scene.hpp"

namespace reveal3d::core {

Geometry::Geometry() : id_ { id::invalid } {}

Geometry::Geometry(id_t id) : id_ { id } {}

Geometry::Geometry(Geometry &other) : id_ {other.Id()} {}

Geometry::Geometry(Geometry &&other)  noexcept : id_ {other.Id()} {}

Geometry& Geometry::operator=(const Geometry &other) {
    id_ = other.id_;
    return *this;
}
Geometry &Geometry::operator=(Geometry &&other) noexcept {
    id_ = other.id_;
    return *this;
}

// Note: for now we only will have one mesh and submesh so we move the vector
// instead of appending it
void Geometry::AddMesh(render::Mesh &mesh) {
    render::SubMesh subMesh;
    Pool().Mesh(id_) = std::move(mesh);

    subMesh.vertexPos = VertexCount();
    subMesh.indexPos = 0;
    subMesh.indexCount = IndexCount();
}


void Geometry::AddMesh(Geometry::primitive type) {

    render::SubMesh &subMesh = Pool().SubMeshes(id_)[0]; // Only one submesh for now

    subMesh.vertexPos = VertexCount();
    subMesh.indexPos = IndexCount();
    subMesh.indexCount = IndexCount();

    switch (type) {
        case cube:       content::GetCubeData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
        case plane:      content::GetPlaneData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
        case cylinder:   content::GetCylinderData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
        case sphere:     content::GetSphereData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
        case cone:       content::GetConeData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
        case torus:      content::GetTorusData(Pool().Mesh(id_).vertices, Pool().Mesh(id_).indices); break;
    }

    subMesh.indexCount = IndexCount() - subMesh.indexCount;
}

GeometryPool &Geometry::Pool() {
    return core::scene.ComponentPool<Geometry>();
}

u32 Geometry::VertexCount() const {
    return Pool().Mesh(id_).vertices.size();
}

u32 Geometry::IndexCount() const {
    return Pool().Mesh(id_).indices.size();
}

std::span<render::SubMesh> Geometry::SubMeshes() const {
    return Pool().SubMeshes(id_);
}

std::vector<render::Vertex> &Geometry::Vertices() const{
    return Pool().Mesh(id_).vertices;
}

std::vector<u32> &Geometry::Indices() const{
    return Pool().Mesh(id_).indices;
}

void Geometry::SetVisibility(bool visibility) {
    Pool().SubMeshes(id_)[0].visible = visibility;
}

bool Geometry::IsVisible() const {
    return Pool().SubMeshes(id_)[0].visible;
}
const render::Material &Geometry::Material(){
   return Pool().Material(id_);
}

void Geometry::SetDiffuseColor(math::vec4 color) {
    Pool().Material(id_).baseColor = color;
    SetDirty();
}

void Geometry::SetFresnel(math::vec3 fresnel) {
    Pool().Material(id_).fresnel = fresnel;
    SetDirty();
}

void Geometry::SetMatTransform(math::mat4 transform) {
    Pool().Material(id_).matTransform = transform;
    SetDirty();
}

void Geometry::SetRoughness(f32 roughness) {
    Pool().Material(id_).roughness = roughness;
    SetDirty();
}

u8 Geometry::Dirty() const {
    return Pool().dirties_.at(id::index(id_));
}

void Geometry::UnDirty() const {
    const id_t idx = id::index(id_);
    if (Pool().dirties_.at(idx) != 0) {
        --Pool().dirties_.at(idx);
    } else {
        Pool().dirties_.at(idx) = 0;
    }
}

void Geometry::SetDirty() const {
    const id_t idx = id::index(id_);
    if (Dirty() == 3) {
        return;
   }
    if (Dirty() == 0) {
        Pool().dirtyIds_.insert(idx);
}
    Pool().dirties_.at(idx) = 3;
}

Geometry GeometryPool::AddComponent() {
    components_.emplace_back();
    return components_.at(components_.size() - 1);
}

Geometry GeometryPool::AddComponent(id_t entityId) {
    const id_t geometryId{ id_factory_.New(meshes_.size()) };

    meshes_.emplace_back();
    subMeshes_.emplace_back();
    materials_.emplace_back();
    dirties_.emplace_back(4);
    dirtyIds_.insert(geometryId);
    newGeometries_.push(entityId);

    Add(id::index(entityId), geometryId);
    return components_.at(id::index(entityId));
}

Geometry GeometryPool::AddComponent(id_t entityId, Geometry::InitInfo &&initInfo) {
    const id_t geometryId{ id_factory_.New(meshes_.size()) };

    meshes_.push_back(std::move(initInfo));
    materials_.emplace_back();
    dirties_.emplace_back(4);
    dirtyIds_.insert(geometryId);
    newGeometries_.push(entityId);

    Add(id::index(entityId), geometryId);

    subMeshes_.emplace_back(render::SubMesh {
            .shader = render::opaque,
            .vertexPos = 0,
            .indexPos = 0,
            .indexCount = components_.at(id::index(entityId)).IndexCount(),
            .visible = true,
    });


    return components_.at(id::index(entityId));
}

void GeometryPool::RemoveComponent(id_t id) {
    id_t idx { id::index(id) };
    if (id_factory_.IsAlive(id)) {
        materials_.unordered_remove(idx);
        meshes_.unordered_remove(idx);
        subMeshes_.unordered_remove(idx);
        dirties_.unordered_remove(idx);
        if (dirtyIds_.find(id) != dirtyIds_.end()) {
            dirtyIds_.erase(id);
        }
        delGeometries_.push(id);
        Remove(id);
    }
}

render::Mesh& GeometryPool::Mesh(id_t id) {
    id_t idx = id::index(id);
    assert(id != id::invalid);
    assert(idx < meshes_.size());
    return meshes_.at(idx);
}

std::span<render::SubMesh> GeometryPool::SubMeshes(id_t id) {
    id_t idx = id::index(id);
    assert(id != id::invalid);
    assert(idx < meshes_.size());
    return std::span {subMeshes_.begin() + idx, subMeshes_.begin() + idx + 1};
}

id_t GeometryPool::PopNew() {
    if (newGeometries_.empty()) {
        return id::invalid;
    }
    const auto id = newGeometries_.front();
    newGeometries_.pop();
    return id;
}

id_t GeometryPool::PopRemoved() {
    if (delGeometries_.empty()) {
        return id::invalid;
    }
    const auto id = delGeometries_.front();
    delGeometries_.pop();
    return id;
}

render::Material &GeometryPool::Material(id_t id) {
    return materials_.at(id::index(id));
}

void GeometryPool::Update() {
    for (auto it = dirtyIds_.begin(); it != dirtyIds_.end();) {
        id_t idx = id::index(*it);
        if (dirties_.at(idx) == 0) {
            it = dirtyIds_.erase(it);
        } else {
            ++it;
        }
}
}

}