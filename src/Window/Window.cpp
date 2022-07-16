//
// Created by ikmokhirio on 12.07.2022.
//

#include "Window.h"

namespace Daedalus {

    Window *Window::GetInstance() {
        std::lock_guard<std::mutex> lock(instanceLock);

        return instancePointer;
    }

    Window *Window::instancePointer;
    std::mutex Window::instanceLock;

}