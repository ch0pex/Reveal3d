/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file config.hpp
 * @version 1.0
 * @date 21/03/2024
 * @brief Config engine structs
 *
 * All this structs can be used to configure the system
 */

#pragma once

#include <array>
#include <string_view>
#include "math/math.hpp"

namespace reveal3d::config {

namespace backends {

enum window {
#ifdef WIN32
  win32 = 0,
#endif
  glfw
};

enum renderer {
#ifdef WIN32
  directx11 = 0,
  directx12,
#endif
  vulkan,
  openGl,
  metal
};

#ifdef WIN32

constexpr renderer default_renderer     = directx12;
constexpr window default_window_manager = win32;

#else

constexpr renderer default_renderer     = openGL;
constexpr window default_window_manager = glfw;

#endif

inline renderer get_graphics_backend(std::string_view const name) {
#ifdef WIN32
  if (name == "directx11")
    return directx11;
  if (name == "directx12")
    return directx12;
#endif
  if (name == "vulkan")
    return vulkan;
  if (name == "openGl")
    return openGl;
  return default_renderer;
}

inline window get_window_backend(std::string_view const name) {
#ifdef WIN32
  if (name == "win32")
    return win32;
#endif
  if (name == "glfw")
    return glfw;
  return default_window_manager;
}

} // namespace backends

struct Backends {
  backends::window window {backends::default_window_manager};
  backends::renderer renderer {backends::default_renderer};
};

struct General { };

struct Scene {
  std::array<f32, 4> clearColor = {0.2F, 0.2F, 0.2F, 1.0F};
  bool showGrid                 = true;
};

struct Render {
  struct Graphics {
    backends::renderer backend {backends::directx12};
    u8 max_framerate = 0;
    bool vsync       = true;
    u8 buffer_count  = 3;
    static constexpr u8 max_buffer_count {3};
  };
  struct Lighting {
    f32 ambient_light_intensity    = 0.7F;
    f32 sun_light_intensity        = 0.9F;
    math::vec3 ambient_color       = {1.0F, 1.0F, 1.0F};
    math::vec3 sun_light_color     = {1.0F, 1.0F, 1.0F};
    math::vec3 sun_light_direction = {0.0F, 0.0F, -1.0F};
  };

  Graphics graphics;
  Lighting lighting;
};

struct Window {
  backends::window backend {backends::default_window_manager};
  std::string_view title = "Reveal3D";
  math::vec2 resolution  = {1920, 1080};
};

struct Camera {
  f32 fov            = 90.0F;
  f32 near_plane     = 0.1F;
  f32 far_plane      = 100.0F;
  f32 movement_speed = 5.0F;
  f32 sensitivity    = 50.0F * 0.001F;
  static constexpr math::vec3 world_up {0, 0, 1};
};

inline General general = {};
inline Scene scene     = {};
inline Render render   = {};
inline Window window   = {};
inline Camera camera   = {};

} // namespace reveal3d::config
