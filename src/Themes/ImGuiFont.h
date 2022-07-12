//
// Created by ikmokhirio on 12.07.2022.
//

#ifndef DAEDALUS_IMGUIFONT_H
#define DAEDALUS_IMGUIFONT_H

#include <imgui.h>
#include "Core.h"
#include <string>
#include <vector>

namespace Daedalus {

    enum Languages {
        None = 0,
        English = BIT(0),
        Russian = BIT(1),
        Custom = BIT(3)
    };

    class ImGuiFont {
    private:
        ImFontConfig config;

        ImWchar *characterRanges;

        std::vector<std::string> files;

        float fontSize;
    public:

        explicit ImGuiFont(std::vector<std::string> filepathes, float size = 16.0f, int languages = English, ImWchar *customRange = nullptr);

        explicit ImGuiFont(std::string filepath, float size = 16, int languages = English, ImWchar *customRange = nullptr);

        ImFontConfig &GetConfig();

        void ApplyToImGuiIo(ImGuiIO *io);

        void SetFontSize(float size);

        void SetLanguages(int languages);

        const std::vector<std::string> &Files();

        ~ImGuiFont();


    };
}


#endif //DAEDALUS_IMGUIFONT_H
