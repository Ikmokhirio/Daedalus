//
// Created by ikmokhirio on 26.06.2022.
//

#include <Daedalus.h>

class TestWindow : public Daedalus::Win32Window {
private:

public:

    TestWindow() : Daedalus::Win32Window() {

    }

    void render() {
        this->NewFrame();

        ImGui::SetWindowPos({0,0});
        ImGui::SetWindowSize({1280,800});
        ImGui::Begin("TEST1");
        ImGui::Text("TEXT");
        ImGui::Button("BUTTON");
        ImGui::End();
        this->EndFrame();
    }

    ~TestWindow() = default;
};

Daedalus::Window *Daedalus::CreateGui() {
    return new TestWindow;
}