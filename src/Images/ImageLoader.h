//
// Created by ikmokhirio on 17.08.2022.
//

#ifndef DAEDALUS_IMAGELOADER_H
#define DAEDALUS_IMAGELOADER_H

#include <string>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <imgui.h>

#include "ImageDescriptor.h"

namespace Daedalus {
    extern void DisplayImage(const ImageDescriptor &desc, const ImVec2& size = ImVec2(0,0), const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
}

#ifdef DAEDALUS_PLATFORM_WINDOWS

ImageDescriptor LoadImageFromPath(LPDIRECT3DDEVICE9 *pDevice, std::string_view path, int width, int height);

#endif


#endif //DAEDALUS_IMAGELOADER_H
