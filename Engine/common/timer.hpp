/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file timer.hpp
 * @version 1.0
 * @date 06/03/2024
 * @brief Timer class header file
 *
 * This file declares the timer class used in the library
 * to deal with time, deltatime, etc...
 *
 */

#pragma once

#include "primitive_types.hpp"
#include "platform.hpp"
#include "input/input.hpp"
#include <chrono>


namespace reveal3d {

class Timer {
public:
    Timer();

    [[nodiscard]] f32 TotalTime() const;
    [[nodiscard]] f32 DeltaTime() const { return static_cast<f32>(deltaTime_); }
    [[nodiscard]] f32 FrameTime() const { return static_cast<f32>(frameTime_); }
    [[nodiscard]] f32 Fps() const { return static_cast<f32>(1 / deltaTime_); }
    [[nodiscard]] f64 MeanFps() const { return static_cast<f64>(totalFrames_) / static_cast<f64>(TotalTime()); }
    [[nodiscard]] f64 AverageFPS() const { return fps_; }
    [[nodiscard]] u64 TotalFrames() const { return totalFrames_; }
    [[nodiscard]] bool IsRunning() { return !stopped_; };
    [[nodiscard]] f32 Diff(f32 time) const;

    void Reset();
    void Start();
    void Stop();
    void Tick();
    void Pause(input::action act, input::type type);

private:

#ifdef _WIN32
    static INLINE void QueryFrequency(i64 &time) { QueryPerformanceFrequency((LARGE_INTEGER *) &time); }
    static INLINE void QueryCounter(i64 &time) { QueryPerformanceCounter((LARGE_INTEGER *) &time); }
#else
    static INLINE void QueryFrequency(i64 &time) { time = 1000000000; }
    static INLINE void QueryCounter(i64 &time) {
        auto now = std::chrono::high_resolution_clock::now();
        auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
        ime = now_ns.time_since_epoch().count();
    }

#endif
    input::System<Timer> inputSystem_;

    f64 secondPerCount_;
    i64 countsPerSecond_;
    f64 deltaTime_; // Affected by pause
    f64 frameTime_; // Non afected by pause

    i64 baseTime_;
    i64 pausedTime_;
    i64 stopTime_;
    i64 prevTime_;
    i64 currTime_;

    u64 totalTime_;
    u64 prevTotalFrames_;
    u64 fps_;
    u64 totalFrames_;
    bool stopped_;

};


}



