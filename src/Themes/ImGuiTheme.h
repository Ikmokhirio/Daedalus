//
// Created by ikmokhirio on 12.07.2022.
//

#ifndef LOKI_IMGUITHEME_H
#define LOKI_IMGUITHEME_H

#include <imgui.h>
#include <vector>
#include "ImGuiFont.h"

namespace Daedalus {
    class ImGuiTheme {
    protected:
        std::vector<ImGuiFont> fonts;
    public:

        ImGuiTheme() = default;

        ImGuiTheme(std::vector<ImGuiFont> primaryMergedFonts, std::vector<ImGuiFont> additionalFonts); // Additional fonts does not require merge option

        virtual std::vector<ImFont*> ApplyTheme(ImGuiIO *io, ImGuiStyle *style = nullptr) = 0;

        virtual ~ImGuiTheme() = default;
    };
}


#endif //LOKI_IMGUITHEME_H