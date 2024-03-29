//
// Created by ikmokhirio on 16.07.2022.
//

#include <Daedalus.h>
#include <EntryPoint.h>
#include <iostream>

class TestWindow : public Daedalus::Win32Window {
private:

    ImageDescriptor testImage;

public:

    explicit TestWindow(Daedalus::WindowProps props) : Daedalus::Win32Window(std::move(props)) {
        try {
            testImage = LoadImageFromPath(GetDevicePointer(), "cat.jpg", 100, 100);
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Render() override {
        NewFrame();

        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowSize({1280, 800});

        ImGui::Begin("TEST");
        ImGui::Text("Hello, world!");

        // Image can be drawn likes this
//        ImGui::Image(testImage.textureId,ImVec2{1024,1204}, ImVec2{0.0f,0.0f},{ImVec2{2.0f,2.0f}});

        // Or like this (this method is safer, because you wouldn't need to do addtional check
        if(Daedalus::DisplayImageButton(testImage, ImVec2(testImage.width, testImage.height), ImVec2(0, 0),ImVec2(1, 1), 1,ImVec4(1,0,0,1), ImVec4(1,1,1,1))) {
            DS_INFO("TEST");
        }

        ImGui::End();

        EndFrame();
    }

    ~TestWindow() = default;
};

Daedalus::Window *Daedalus::CreateGui() {
    return new TestWindow({"Example window", NoStyle, 1280, 800, 19});
}