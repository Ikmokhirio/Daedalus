//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_ENTRYPOINT_H
#define DAEDALUS_ENTRYPOINT_H

#include "Window/Window.h"
#include "Logger.h"

int __stdcall wWinMain(HINSTANCE hinstance,
                       HINSTANCE prevInstance,
                       PWSTR args,
                       int commandShow) {

    AllocConsole();
    Daedalus::Logger::InitLogger();

    DS_INFO("Starting app...");
    auto gui = Daedalus::CreateGui();

    while(gui->IsOpen()) {
        gui->render();
    }

    delete gui;

    return EXIT_SUCCESS;
}

#endif //DAEDALUS_ENTRYPOINT_H
