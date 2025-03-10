/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file glfw.hpp
 * @version 1.0
 * @date 27/02/2024
 * @brief Short description
 *
 * GLFW backend manager class
 */

#pragma once

#include "input/input.hpp"
#include "render/renderer.hpp"
#include "window/window_info.hpp"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "utils.hpp"


namespace reveal3d::window {


class Glfw {
public:
  explicit Glfw(Descriptor const& info);

  template<graphics::HRI Gfx>
  void create(render::Renderer<Gfx>& renderer);
  void show();
  template<graphics::HRI Gfx>
  void update(render::Renderer<Gfx>& renderer);
  void closeWindow(input::Action act, input::type type);
  bool shouldClose();

  [[nodiscard]] Resolution getRes() const { return info_.res; }
  [[nodiscard]] WHandle getHandle() const { return info_.handle; }

private:
  template<graphics::HRI Gfx>
  void clipMouse(render::Renderer<Gfx>& renderer);

  Descriptor info_;
  GLFWwindow* window_pointer_;
};

template<graphics::HRI Gfx>
void Glfw::update(render::Renderer<Gfx>& renderer) {
  // Handle inputs
  glfwPollEvents();
}

template<graphics::HRI Gfx>
void Glfw::create(render::Renderer<Gfx>& renderer) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (not glfw::create_window(info_)) {
    glfwTerminate();
    logger(LogError) << "Error creating GLFW window, app will terminate.";
    std::terminate();
  }

  glfwSwapInterval(0);
}

template<graphics::HRI Gfx>
void Glfw::clipMouse(render::Renderer<Gfx>& renderer) { }

} // namespace reveal3d::window
