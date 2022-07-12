//
// Created by ikmokhirio on 12.07.2022.
//

#include "ImGuiTheme.h"
#include <utility>

namespace Daedalus {
    ImGuiTheme::ImGuiTheme(std::vector<ImGuiFont> setupFonts) {
        fonts = std::move(setupFonts);
    }
}
