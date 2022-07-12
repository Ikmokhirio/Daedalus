//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_WINDOW_H
#define DAEDALUS_WINDOW_H

#include <string>
#include <mutex>
#include <utility>

#include "Themes/ImGuiTheme.h"
#include "Core.h"
#include "imgui.h"

namespace Daedalus {

    enum WindowStyle {
        NoStyle = 0,
        Minimizing = BIT(1),
        Resizing = BIT(2),
        CustomTitleBar = BIT(3)
    };

    struct WindowProps {
        std::string windowName;
        uint32_t width{};
        uint32_t height{};
        uint32_t titleBarHeight;
        int style;

        WindowProps(std::string n,int newStyle, uint32_t w = 800, uint32_t h = 600, uint32_t title=20) :
                windowName(std::move(n)),
                style(newStyle),
                width(w),
                height(h),
                titleBarHeight(title) {

        }

        WindowProps() = default;
    };


    class Window {
    private:

        static Window *instancePointer;
        static std::mutex instanceLock;

    protected:
        bool isOpen = true;

        WindowProps windowProps;

        explicit Window(WindowProps props) {
            instancePointer = this;
            windowProps = std::move(props);
        }

    public:

        virtual void render() = 0;

        inline bool IsOpen() const { return isOpen; }

        inline void Open() { isOpen = true; }

        inline void Close() { isOpen = false; }

        static Window *GetInstance();

        Window(Window &other) = delete;

        void operator=(const Window &other) = delete;

    };
}

#ifdef DAEDALUS_PLATFORM_WINDOWS

#include "Window/ImGuiBackends/imgui_impl_dx9.h"
#include "Window/ImGuiBackends/imgui_impl_win32.h"
#include "Logger.h"
#include <d3d9.h>
#include <tchar.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern LRESULT WINAPI oWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Daedalus {

    class Win32Window : public Window {
    public:
        explicit Win32Window(WindowProps props);

        void NewFrame();

        void EndFrame();

        void SetNextTheme(ImGuiTheme *theme);

        virtual void DrawTitleBar();

        LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        ~Win32Window();

    private:
        D3DPRESENT_PARAMETERS presentParameters = {};
        LPDIRECT3D9 d3d = NULL;
        LPDIRECT3DDEVICE9 device = NULL;

        HWND windowHandle = NULL;
        POINTS position = { };
        WNDCLASSEX windowClass = {};

        ImGuiTheme *nextTheme;

        void ChangeTheme();

        void CreateWin32Window();

        void DestroyWin32Window();

        void CreateDevice();

        void ResetDevice();

        void DestroyDevice();

        void CreateImGui();

        void DestroyImGui();
    };

    Window *CreateGui();
}

#endif

#endif //DAEDALUS_WINDOW_H
