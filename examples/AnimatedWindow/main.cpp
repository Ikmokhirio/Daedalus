//
// Created by ikmokhirio on 16.07.2022.
//

#include <Daedalus.h>
#include <EntryPoint.h>

class TestWindow : public Daedalus::Win32Window {
private:
    float myAnimatedParams;

    Animation *colorAnim;
public:

    explicit TestWindow(Daedalus::WindowProps props) : Daedalus::Win32Window(std::move(props)) {
        myAnimatedParams = 0.0f;
        colorAnim = new Animation(myAnimatedParams, 0.0f, 1.0f, EaseOutSine, 1.0f);
    }

    void Render() override {
        NewFrame();

        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowSize({1280, 800});

        ImGui::Begin("TEST");
        // Changing text color from black to red and backwards
        if(colorAnim->Play()) {
            colorAnim->Reverse();
        }
        ImGui::TextColored(ImColor(myAnimatedParams, 0.0f, 0.0f, 1.0f), "Hello, world!");
        ImGui::End();

        EndFrame();
    }

    ~TestWindow() = default;
};

Daedalus::Window *Daedalus::CreateGui() {
    return new TestWindow({"Example window", Resizing, 1280, 800});
}