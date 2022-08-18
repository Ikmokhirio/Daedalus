//
// Created by ikmokhirio on 15.07.2022.
//

#include "Win32Window.h"
#include <utility>

#ifdef DAEDALUS_PLATFORM_WINDOWS

namespace Daedalus {

    Win32Window::Win32Window(WindowProps props) : Window(std::move(props)) {

        CreateWin32Window();

        CreateDevice();

        CreateImGui();

        Open();

        RECT actualSize;
        GetClientRect(windowHandle, &actualSize);
        windowProps.width = actualSize.right - actualSize.left;
        windowProps.height = actualSize.bottom - actualSize.top;
    }

    void Win32Window::NewFrame() {
        MSG message;
        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
            if (!isOpen) {
                // OnExitHandler();
                exit(0);
            }
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Allow to have full screen window))))
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize(ImVec2(windowProps.width, windowProps.height));
        // Add rewriting params via props
        auto options = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (windowProps.style & CustomTitleBar) {
            options |= ImGuiWindowFlags_NoTitleBar;
        }

        if (!ImGui::Begin(windowProps.windowName.c_str(), &isOpen, options)) {

        }

        if (windowProps.style & CustomTitleBar) {
            // Tittle bar
            DrawTitleBar();
        }
    }

    void Win32Window::DrawTitleBar() {
        throw std::runtime_error("No implementation for DrawTitleBar");
    }

    void Win32Window::EndFrame() {
        ImGui::End();
        ImGui::EndFrame();

        device->SetRenderState(D3DRS_ZENABLE, FALSE);
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

        device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

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

    Win32Window::~Win32Window() {
        DestroyImGui();
        DestroyDevice();
        DestroyWin32Window();
    }

    LRESULT WINAPI oWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        return reinterpret_cast<Win32Window *>(Win32Window::GetInstance())->WndProc(hWnd, msg, wParam, lParam);
    }

    LRESULT WINAPI Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;


        switch (msg) {
            case WM_SIZING: {

                return 0;
            }
            case WM_SIZE: {
                if (device != NULL && wParam != SIZE_MINIMIZED) {
                    presentParameters.BackBufferWidth = LOWORD(lParam);
                    presentParameters.BackBufferHeight = HIWORD(lParam);
                    windowProps.width = LOWORD(lParam);
                    windowProps.height = HIWORD(lParam);
                    ResetDevice();
                    return 0;
                }
                if (wParam == SIZE_MAXIMIZED) {
                    // Disable collapse
                }
                break;
            }
            case WM_SYSCOMMAND:
                if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                    return 0;
                break;
            case WM_DESTROY:
                Daedalus::Window::GetInstance()->Close();
                PostQuitMessage(0);
                return 0;
            case WM_LBUTTONDOWN:
                position = MAKEPOINTS(lParam); // set click points
                break;
            case WM_MOUSEMOVE: { // ImGui Window movement according to win32 window
                if (wParam == MK_LBUTTON) {
                    const auto points = MAKEPOINTS(lParam);
                    auto rect = ::RECT{};

                    GetWindowRect(windowHandle, &rect);

                    rect.left += points.x - position.x;
                    rect.top += points.y - position.y;

                    if (position.x >= 0 &&
                        position.x <= windowProps.width &&
                        position.y >= 0 && position.y <= windowProps.titleBarHeight)
                        SetWindowPos(
                                windowHandle,
                                HWND_TOPMOST,
                                rect.left,
                                rect.top,
                                0, 0,
                                SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
                        );
                }
            }
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void Win32Window::CreateWin32Window() {
        windowClass = {
                sizeof(WNDCLASSEX),
                CS_CLASSDC, // style
                oWndProc, // lpfnWndProc
                0L, // .cbClsExtra
                0L, // cbWndExtra
                GetModuleHandle(NULL), // hInstance
                NULL, // hIcon
                NULL, // hCursor
                NULL, // hbrBackground
                NULL, // lpszMenuName
                windowProps.windowName.c_str(), // lpszClassName
                NULL // hIconsm
        };

        DS_CORE_INFO("Register window class");
        RegisterClassEx(&windowClass);

        DS_CORE_INFO("Creating window with name : {0}, width : {1}, height : {2}",
                     windowProps.windowName,
                     windowProps.width,
                     windowProps.height);

        // TOPMOST - ON TOP OF ALL WINDOWS
        // TRANSPARENT - CLICK THROUGH WINDOW
        // LAYERED - SET TRANSPARANCY COLOR

        DWORD wStyle = WS_POPUP;

        if (windowProps.style & Resizing) {
            wStyle |= WS_SIZEBOX;
        }

        windowHandle = CreateWindowEx(0,
                                      windowClass.lpszClassName,
                                      windowProps.windowName.c_str(),
                                      wStyle,
                                      100,
                                      100,
                                      windowProps.width, windowProps.height, NULL, NULL, windowClass.hInstance, NULL);

        ShowWindow(windowHandle, SW_SHOWDEFAULT);
        UpdateWindow(windowHandle);

    }

    void Win32Window::DestroyWin32Window() {
        DestroyWindow(windowHandle);
        UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    }

    void Win32Window::ResetDevice() {
        ImGui_ImplDX9_InvalidateDeviceObjects();

        const auto result = device->Reset(&presentParameters);

        if (result == D3DERR_INVALIDCALL) {
            DS_CORE_ERROR("Invalid call during ResetDevice()");
            return;
        }

        ImGui_ImplDX9_CreateDeviceObjects();
    }

    void Win32Window::DestroyDevice() {
        if (device) {
            device->Release();
            device = nullptr;
        }

        if (d3d) {
            d3d->Release();
            d3d = nullptr;
        }
    }

    void Win32Window::DestroyImGui() {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    void Win32Window::CreateImGui() {

//        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = NULL;

        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        DS_CORE_INFO("Initializing imgui");
        ImGui_ImplWin32_Init(windowHandle);
        ImGui_ImplDX9_Init(device);
    }

    void Win32Window::CreateDevice() {
        if ((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
            DS_CORE_ERROR("Cannot create d3d9 object");
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
            DS_CORE_ERROR("Cannot create d3d9 device");
            return;
        }

    }

    std::vector<ImFont*> Win32Window::SetNextTheme(ImGuiTheme *theme) {
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->Clear();

        std::vector<ImFont*> result= theme->ApplyTheme(&ImGui::GetIO(), &ImGui::GetStyle());

        ResetDevice();

        theme = nullptr;

        return result;
    }

    void Win32Window::Collapse() {
        CloseWindow(windowHandle);
    }

    LPDIRECT3DDEVICE9 *Win32Window::GetDevicePointer() {
        return &device;
    }
}

#endif