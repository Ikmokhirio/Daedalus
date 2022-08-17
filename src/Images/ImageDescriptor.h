//
// Created by ikmokhirio on 17.08.2022.
//

#ifndef DAEDALUS_IMAGEDESCRIPTOR_H
#define DAEDALUS_IMAGEDESCRIPTOR_H


#include <string_view>

struct ImageDescriptor {

    std::string_view filepath;

    void *textureId; // At least that what it called in imgui sources :)

    int width;

    int height;
};


#endif //DAEDALUS_IMAGEDESCRIPTOR_H
