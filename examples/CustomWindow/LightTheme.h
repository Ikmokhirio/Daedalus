//
// Created by ikmokhirio on 12.07.2022.
//

#ifndef DAEDALUSEXAMPLE_LIGHTTHEME_H
#define DAEDALUSEXAMPLE_LIGHTTHEME_H

#include <Daedalus.h>

class LightTheme : public Daedalus::ImGuiTheme{
public:

    LightTheme(std::vector<Daedalus::ImGuiFont> primaryFonts, std::vector<Daedalus::ImGuiFont> additionalFonts);

    std::vector<ImFont*> ApplyTheme(ImGuiIO *io, ImGuiStyle *style = nullptr) override;

    ~LightTheme() = default;
};


#endif //DAEDALUSEXAMPLE_LIGHTTHEME_H
