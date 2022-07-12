//
// Created by ikmokhirio on 12.07.2022.
//

#include "ImGuiFont.h"

#include <utility>
#include <Logger.h>

namespace Daedalus {

    ImGuiFont::ImGuiFont(std::vector<std::string> filepathes, float size, int languages, ImWchar *customRange) {
        characterRanges = nullptr;
        files = std::move(filepathes);

        DS_CORE_INFO("Creating font");

        config.MergeMode = true;

        if((languages & Russian) && (languages & English)) {
            characterRanges = new ImWchar[5]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0x0400, 0x044F, // Cyrillic
                            0,
                    };
        } else if (languages & Russian) {
            characterRanges = new ImWchar[3]
                    {
                            0x0400, 0x044F, // Cyrillic
                            0,
                    };
        } else if (languages & English) {
            characterRanges = new ImWchar[3]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0,
                    };
        }

        if(languages & Custom) {
            delete characterRanges;
            if(!customRange) {
                DS_CORE_ERROR("No custom range provided for font");
                throw std::runtime_error("No custom range provided for font");
            }
            characterRanges = customRange;
        }

        fontSize = size;
    }

    ImGuiFont::ImGuiFont(std::string filepath, float size, int languages, ImWchar *customRange) {
        DS_CORE_INFO("Creating font");
        characterRanges = nullptr;
        files.emplace_back(std::move(filepath));

        if((languages & Russian) && (languages & English)) {
            characterRanges = new ImWchar[5]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0x0400, 0x044F, // Cyrillic
                            0,
                    };
        } else if (languages & Russian) {
            characterRanges = new ImWchar[3]
                    {
                            0x0400, 0x044F, // Cyrillic
                            0,
                    };
        } else if (languages & English) {
            characterRanges = new ImWchar[3]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0,
                    };
        }

        if(languages & Custom) {
            delete characterRanges;
            if(!customRange) {
                DS_CORE_ERROR("No custom range provided for font");
                throw std::runtime_error("No custom range provided for font");
            }
            characterRanges = customRange;
        }

        fontSize = size;
    }


    ImGuiFont::~ImGuiFont() {
        /// Should be deleted on imgui side
        /// TODO : Check possible memory leak
//        delete characterRanges;
    }

    ImFontConfig &ImGuiFont::GetConfig() {
        return config;
    }

    const std::vector<std::string> &ImGuiFont::Files() {
        return files;
    }

    void ImGuiFont::SetFontSize(float size) {
        fontSize = size;
    }

    void ImGuiFont::SetLanguages(int languages) {
        delete characterRanges;

        if (languages & Russian) {
            characterRanges = new ImWchar[5]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0x0400, 0x044F, // Cyrillic
                            0,
                    };
        } else {
            characterRanges = new ImWchar[3]
                    {
                            0x0020, 0x00FF, // Basic Latin + Latin Supplement
                            0,
                    };
        }
    }

    void ImGuiFont::ApplyToImGuiIo(ImGuiIO *io) {
        for (const auto &file: files) {
            io->Fonts->AddFontFromFileTTF(file.c_str(), fontSize, &config, characterRanges);
        }
    }

}