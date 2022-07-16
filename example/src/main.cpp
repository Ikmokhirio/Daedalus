//
// Created by ikmokhirio on 26.06.2022.
//

#include <Daedalus.h>
#include "LightTheme.h"
#include <EntryPoint.h>
#include <utility>
#include <Windows.h>

#include "FontAwesome6.h"

class TestWindow : public Daedalus::Win32Window {
private:
    float test;
    bool reverse;
public:

    explicit TestWindow(Daedalus::WindowProps props) : Daedalus::Win32Window(std::move(props)) {
        test = 0;
        reverse = false;
        // Default font
        Daedalus::ImGuiFont robotoFont(R"(C:\Roboto-Medium.ttf)", 24.0f, Daedalus::Russian | Daedalus::English);
        robotoFont.GetConfig().OversampleH = 1; //or 2 is the same
        robotoFont.GetConfig().OversampleV = 1;
        robotoFont.GetConfig().PixelSnapH = 1;

        // Custom font
        std::vector<std::string> icons = {
                R"(C:\fa-regular-400.ttf)",
                R"(C:\fa-solid-900.ttf)"
        };
        auto *iconRanges = new ImWchar[3]{
                ICON_MIN_FA, ICON_MAX_FA, 0
        };
        Daedalus::ImGuiFont iconsFont(icons, 24.0f, Daedalus::Custom, iconRanges);
        iconsFont.GetConfig().GlyphMinAdvanceX = 13.0f;

        SetNextTheme(new LightTheme({robotoFont, iconsFont}));
    }

    void render() {
        NewFrame();

        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowSize({1280, 800});
        ImGui::Begin("TEST");
        ImGui::Text(" РУССКИЙ ТЕКСТ И " ICON_FA_USERS " иконка с %f временем", ImGui::GetIO().DeltaTime);
        ImGui::Button("BUTTON");

        if (!reverse && test < 1.0f) {
            AnimateStep(test, 0, 1.0f, EaseOutSine, 1.0f);
        }
        if(reverse && test > 0.0f) {
            AnimateStep(test, 1.0f, 0.0f, EaseOutSine, 1.0f);
            DS_INFO("{0}", test);
        }
        if(test == 1.0f) {
            reverse = true;
        }
        if(test == 0.0f) {
            reverse = false;
        }
        ImGui::TextColored(ImColor(test, test, test), "Test hi))");
        ImGui::End();

        EndFrame();
    }

    ~TestWindow() = default;
};

Daedalus::Window *Daedalus::CreateGui() {
    return new TestWindow({"Test", Resizing | Minimizing | CustomTitleBar, 1280, 800});
}