//
// Created by ikmokhirio on 16.07.2022.
//

#include <Daedalus.h>
#include <EntryPoint.h>

class TestWindow : public Daedalus::Win32Window {
private:
public:

    explicit TestWindow(Daedalus::WindowProps props) : Daedalus::Win32Window(std::move(props)) {
    }

    void Render() override {
        NewFrame();

        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowSize({1280, 800});

        ImGui::Begin("TEST");
        ImGui::Text("Hello, world!");
        ImGui::End();

        EndFrame();
    }

    ~TestWindow() = default;
};

Daedalus::Window *Daedalus::CreateGui() {
    return new TestWindow({"Example window", Resizing, 1280, 800});
}