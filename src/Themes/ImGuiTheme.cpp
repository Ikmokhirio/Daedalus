//
// Created by ikmokhirio on 12.07.2022.
//

#include "ImGuiTheme.h"
#include <utility>

namespace Daedalus {
    ImGuiTheme::ImGuiTheme(std::vector<ImGuiFont> primaryMergedFonts, std::vector<ImGuiFont> additionalFonts) {
        fonts = std::move(primaryMergedFonts);
        if (fonts.size() > 1) {
            for (int i = 1; i < fonts.size(); i++) {
                fonts[i].GetConfig().MergeMode = true;
            }
        }

        fonts.insert(fonts.end(), additionalFonts.begin(), additionalFonts.end());
    }
}
