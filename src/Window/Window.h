//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_WINDOW_H
#define DAEDALUS_WINDOW_H

#include <string>
#include <mutex>
#include <utility>

#include "Utils/Utils.h"
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
        std::string windowName{};
        uint32_t width{};
        uint32_t height{};
        uint32_t titleBarHeight{};
        int style{};

        WindowProps(std::string n, int newStyle, uint32_t w = 800, uint32_t h = 600, uint32_t title = 20) :
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


#endif //DAEDALUS_WINDOW_H
