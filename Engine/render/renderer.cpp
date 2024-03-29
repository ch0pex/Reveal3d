/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file renderer_.cpp
 * @version 1.0
 * @date 25/02/2024
 * @brief Short description
 *
 * Longer description
 */

#include "renderer.hpp"

namespace reveal3d::render {

template<graphics::HRI Gfx>
Renderer<Gfx>::Renderer(window::Resolution *res, core::Scene &scene) :
        camera_(*res),
        graphics_(res),
        scene_(scene)
{

}

template<graphics::HRI Gfx>
void Renderer<Gfx>::Init(WHandle wHandle) {
    f32 time = timer_.TotalTime();
    graphics_.SetWindow(wHandle);
    graphics_.LoadPipeline();
    log(logDEBUG) << "Initializing Pipeline...[" << timer_.Diff(time) * 1000 <<"ms]";
    time = timer_.TotalTime();
    graphics_.LoadAssets(scene_);
    log(logDEBUG) << "Loading assets...[" << timer_.Diff(time) * 1000 <<"ms]";
}

template<graphics::HRI Gfx>
void Renderer<Gfx>::Update() {
    timer_.Tick();
    camera_.Update(timer_);
    graphics_.Update(camera_, timer_);
}

template<graphics::HRI Gfx>
void Renderer<Gfx>::Render() {
    graphics_.PrepareRender();
    graphics_.Draw();
}

template<graphics::HRI Gfx>
void Renderer<Gfx>::Destroy() {
    log(logDEBUG) << "Cleaning pipeline...[" << timer_.TotalTime()  <<"]";
    graphics_.Terminate();
}

template<graphics::HRI Gfx>
void Renderer<Gfx>::Resize(const window::Resolution &res) {
    camera_.Resize(res);
    graphics_.Resize(res);
}

template class Renderer<graphics::dx::Graphics>;

} // namespace reveal3d::render
