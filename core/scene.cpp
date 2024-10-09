/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file scene.cpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Scene
 *
 * Scene IDs implementation
 */

#include "scene.hpp"
#include "render/light.hpp"

namespace reveal3d::core {

Scene scene;

Entity::Entity(u32 id) : id_ {id} { }

bool Entity::IsAlive() {
    return core::scene.IsEntityAlive(id_);
}

Scene::Scene() : rootNode_(0), lastNode_(id::invalid) {}


Entity Scene::NewEntity() {
    Entity entity(idFactory_.New());

    Node node {
        .entity = entity
    };

    if (id::isValid(lastNode_)) {
       node.prev = sceneGraph_.at(lastNode_).entity;
       sceneGraph_.at(lastNode_).next = node.entity;
    }

    if (id::index(entity.Id()) < sceneGraph_.size()) {
        sceneGraph_.at(id::index(entity.Id())) = node;
    } else {
        sceneGraph_.push_back(node);
        transformPool_.AddComponent(entity.Id());
        metadataPool_.AddComponent(entity.Id());
        geometryPool_.AddComponent();
    }

    lastNode_ = id::index(entity.Id());

    return entity;
}

Entity Scene::NewChildEntity(id_t parent) { return NewChildEntity(Entity(parent)); }

Entity Scene::NewChildEntity(Entity parent) {
    assert(parent.IsAlive());

    Entity child(idFactory_.New());

    Node childNode {
            .entity = child,
            .parent = parent
    };

    Node& parentNode = GetNode(parent.Id());

    if (not parentNode.firstChild.IsAlive()) {
       parentNode.firstChild = child;
    } else {
        Node& firstChild = GetNode(parentNode.firstChild.Id());
        firstChild.prev = childNode.entity;
        childNode.next = parentNode.firstChild;
        parentNode.firstChild = childNode.entity;
    }

    if (id::index(child.Id()) < sceneGraph_.size()) {
        sceneGraph_.at(id::index(child.Id())) = childNode;
    } else {
        sceneGraph_.push_back(childNode);
        transformPool_.AddComponent(child.Id());
        metadataPool_.AddComponent(child.Id());
        geometryPool_.AddComponent();
    }

    return child;
}

Entity Scene::RemoveEntity(id_t id) {
    Entity entity { id };
    Entity nextOrPrev = {};
    if (idFactory_.IsAlive(id)) {
        if (IsEntityAlive(GetNode(id).next.Id())) nextOrPrev = GetNode(id).next;
        else if (IsEntityAlive(GetNode(id).prev.Id())) nextOrPrev = GetNode(id).prev;
        RemoveNode(id);
        transformPool_.RemoveComponent(id);
        geometryPool_.RemoveComponent(id);
    }
    return nextOrPrev;
}

void Scene::RemoveNode(id_t id) {
    if (!id::isValid(id)) return;
    Node& node = GetNode(id);
    idFactory_.Remove(id);

    if (node.prev.IsAlive()) {
        Node& prevNode = GetNode(node.prev.Id());
        prevNode.next = node.next;
    } else if (not node.parent.IsAlive()){
       //Change root node
       rootNode_ = node.next.IsAlive() ? node.next.Id() : id::invalid;
    }

    if (node.next.IsAlive()) {
        Node& nextNode = GetNode(node.next.Id());
        nextNode.prev = node.prev;
    } else if (not node.parent.IsAlive()){
        lastNode_ = node.prev.IsAlive() ? node.prev.Id() : id::invalid;
    }

    if (node.firstChild.IsAlive()) {
        auto children = node.GetChildren();
        for (auto child : children) {
            RemoveNode(child);
        }
    }
}

bool Scene::IsEntityAlive(id_t id) {
    return idFactory_.IsAlive(id);
}

void Scene::Init() {
    // Pooling Init
    // transformPool_.Init();
    
    
//    for (u32 i = 0; i < scene.entities_; ++i) {
//        if (scripts_[i] != nullptr) {
//            Entity entity = GetEntity(i);
//            scripts_[i]->Begin(entity);
//        }
//    }
}

//Runs scripts
void Scene::Update(f32 dt) {
    transformPool_.Update();
    geometryPool_.Update();
    scriptPool_.Update();
    metadataPool_.Update();
}

Scene::~Scene() {
//    for(auto *script : scripts_) {
//        delete script;
//    }
}


std::vector<id_t> Scene::Node::GetChildren() {
    std::vector<id_t> children;
    if (firstChild.IsAlive()) {
        Node &currNode = scene.GetNode(firstChild.Id());
        while(true) {
            children.push_back(currNode.entity.Id());
            if (currNode.next.IsAlive()) {
                currNode = scene.GetNode(currNode.next.Id());
            } else {
                break;
            }
        }
    }
    return children;
}

}
