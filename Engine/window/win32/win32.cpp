/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file win32.cpp
 * @version 1.0
 * @date 30/04/2024
 * @brief Short description
 *
 * Longer description
 */

#include "win32.hpp"

namespace reveal3d::window {

Win32::Win32(InitInfo &info) : info_(info)
{
    inputSystem_.AddHandlerDown(input::action::window_close, {&Win32::CloseWindow, nullptr, this});
}

void Win32::Show() {
    ShowWindow(info_.handle.hwnd, SW_SHOW);
    UpdateWindow(info_.handle.hwnd);
    isRunning_ = true;
}

bool Win32::ShouldClose() {
    return !(isRunning_ );
}

void Win32::Update() {
    while (PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg_);
        DispatchMessage(&msg_);
        isRunning_ &= (msg_.message != WM_QUIT);
    }
}

void Win32::CloseWindow(input::action act, input::type type) {
    PostMessage(info_.handle.hwnd, WM_CLOSE, 0, 0);
}

}
