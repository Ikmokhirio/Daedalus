//
// Created by ikmokhirio on 15.07.2022.
//

#ifndef DAEDALUS_WIN32WINDOW_H
#define DAEDALUS_WIN32WINDOW_H

#ifdef DAEDALUS_PLATFORM_WINDOWS

#include "Window/ImGuiBackends/imgui_impl_dx9.h"
#include "Window/ImGuiBackends/imgui_impl_win32.h"
#include "Logger.h"
#include "Window.h"

#include <d3d9.h>
#include <tchar.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Daedalus {

    extern LRESULT WINAPI oWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    class Win32Window : public Window {
    public:
        explicit Win32Window(WindowProps props);

        void Collapse() override;

        void NewFrame();

        void EndFrame();

        std::vector<ImFont*> SetNextTheme(ImGuiTheme *theme);

        virtual void DrawTitleBar();

        LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        LPDIRECT3DDEVICE9 *GetDevicePointer();

        ~Win32Window();

    private:
        D3DPRESENT_PARAMETERS presentParameters = {};
        LPDIRECT3D9 d3d = NULL;
        LPDIRECT3DDEVICE9 device = NULL;

        HWND windowHandle = NULL;
        POINTS position = {};
        WNDCLASSEX windowClass = {};

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

#endif //DAEDALUS_WIN32WINDOW_H
