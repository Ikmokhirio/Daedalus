//
// Created by ikmokhirio on 17.08.2022.
//

#ifndef DAEDALUS_IMAGELOADER_H
#define DAEDALUS_IMAGELOADER_H

#include <string>
#include <d3d9.h>
#include <d3dx9tex.h>

#include "ImageDescriptor.h"

#ifdef DAEDALUS_PLATFORM_WINDOWS

ImageDescriptor LoadImageFromPath(LPDIRECT3DDEVICE9 *pDevice, std::string_view path, int width, int height);

#endif


#endif //DAEDALUS_IMAGELOADER_H
