//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_WINDOW_H
#define DAEDALUS_WINDOW_H

#include "Core.h"
#include "imgui.h"

namespace Daedalus {
    class Window {
    protected:
        bool isOpen = true;

        static Window *instance;

        Window() {
            instance = this;
        }

    public:

        virtual void render() = 0;

        inline bool IsOpen() { return isOpen; }

        inline void Open() { isOpen = true; }

        inline void Close() { isOpen = false; }

        inline static Window *GetInstance() { return instance;}

    };

    Window *Window::instance;
}

#ifdef DAEDALUS_PLATFORM_WINDOWS

#include "Window/ImGuiBackends/imgui_impl_dx9.h"
#include "Window/ImGuiBackends/imgui_impl_win32.h"
#include "Logger.h"
#include <d3d9.h>
#include <tchar.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SIZE:
//            if (device != NULL && wParam != SIZE_MINIMIZED)
//            {
//                presentParameters.BackBufferWidth = LOWORD(lParam);
//                presentParameters.BackBufferHeight = HIWORD(lParam);
//                ResetDevice();
//            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            Daedalus::Window::GetInstance()->Close();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


#endif

namespace Daedalus {

    class Win32Window : public Window {

    private:
        D3DPRESENT_PARAMETERS presentParameters = {};
        LPDIRECT3D9 d3d = NULL;
        LPDIRECT3DDEVICE9 device = NULL;

        HWND windowHandle = NULL;
        WNDCLASSEX windowClass = {};

        void CreateWin32Window() {
            windowClass = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL,
                           NULL, _T("ImGui Example"), NULL};

            DS_INFO("Register window class");
            RegisterClassEx(&windowClass);

            DS_INFO("Creating window");
            windowHandle = CreateWindow(windowClass.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_CAPTION, 100,
                                        100,
                                        1280, 800, NULL, NULL, windowClass.hInstance, NULL);

            ShowWindow(windowHandle, SW_SHOWDEFAULT);
            UpdateWindow(windowHandle);

        }

        void DestroyWin32Window() {
            DestroyWindow(windowHandle);
            UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
        }

        void CreateDevice() {
            if ((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
                DS_ERROR("Cannot create d3d9 object");
                return;
            }

            // Create the D3DDevice
            ZeroMemory(&presentParameters, sizeof(presentParameters));
            presentParameters.Windowed = TRUE;
            presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
            presentParameters.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
            presentParameters.EnableAutoDepthStencil = TRUE;
            presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
            presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
            //presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate

            if (d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &presentParameters, &device) < 0) {
                DS_ERROR("Cannot create d3d9 device");
                return;
            }

        }

        void ResetDevice() {
            ImGui_ImplDX9_InvalidateDeviceObjects();

            const auto result = device->Reset(&presentParameters);

            if (result == D3DERR_INVALIDCALL) {
                DS_ERROR("Invalid call during ResetDevice()");
                return;
            }

            ImGui_ImplDX9_CreateDeviceObjects();
        }

        void DestroyDevice() {
            if (device) {
                device->Release();
                device = nullptr;
            }

            if (d3d) {
                d3d->Release();
                d3d = nullptr;
            }
        }

        void CreateImGui() {

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.IniFilename = NULL;

            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            DS_INFO("Initializing imgui");
            ImGui_ImplWin32_Init(windowHandle);
            ImGui_ImplDX9_Init(device);
        }

        void DestroyImGui() {
            ImGui_ImplDX9_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
        }


    public:
        // Window name
        // Window size
        Win32Window() {

            CreateWin32Window();

            CreateDevice();

            CreateImGui();

            isOpen = true;

        }

        void NewFrame() {

            MSG message;
            while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // Allow to have full screen window))))
            ImGui::SetNextWindowSize(ImVec2(1280, 800));
            if (!ImGui::Begin("TEST",nullptr,ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::End();
                return;
            }
        }

        void EndFrame() {
            ImGui::End();
            ImGui::EndFrame();

            device->SetRenderState(D3DRS_ZENABLE, FALSE);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

            device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(255, 0, 0, 255), 1.0f, 0);

            if (device->BeginScene() >= 0) {
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
                device->EndScene();
            }


            const auto result = device->Present(0, 0, 0, 0);

            // Handle loss of D3D9 device
            if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
                ResetDevice();
        }


        ~Win32Window() {
            DestroyImGui();
            DestroyDevice();
            DestroyWin32Window();
        }
    };

    Window *CreateGui();
}

#endif //DAEDALUS_WINDOW_H
