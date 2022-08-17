//
// Created by ikmokhirio on 17.08.2022.
//

#include "ImageLoader.h"
#include <imgui.h>
#include <Logger.h>

namespace Daedalus {
    void DisplayImage(const ImageDescriptor &desc, const ImVec2 &size, const ImVec2 &uv0, const ImVec2 &uv1,
                      const ImVec4 &tint_col, const ImVec4 &border_col) {

        if (!desc.textureId) {
            DS_ERROR("Texture was not correctly loaded");
            return;
        }

        if (size.x == 0 && size.y == 0) {
            return ImGui::Image(desc.textureId,
                                ImVec2(static_cast<float>(desc.width), static_cast<float>(desc.height)),
                                uv0, uv1, tint_col, border_col);
        }

        return ImGui::Image(desc.textureId, size, uv0, uv1, tint_col, border_col);
    }


    bool DisplayImageButton(const ImageDescriptor &desc, const ImVec2 &size,
                            const ImVec2 &uv0, const ImVec2 &uv1, int frame_padding,
                            const ImVec4 &bg_col, const ImVec4 &tint_col) {

        if (!desc.textureId) {
            DS_ERROR("Texture was not correctly loaded");
            return false;
        }

        if (size.x == 0 && size.y == 0) {
            return ImGui::ImageButton(desc.textureId,
                                      ImVec2(static_cast<float>(desc.width), static_cast<float>(desc.height)),
                                      uv0, uv1, frame_padding, bg_col, tint_col);
        }

        return ImGui::ImageButton(desc.textureId, size,
                                  uv0, uv1, frame_padding, bg_col, tint_col);
    }
}

#ifdef DAEDALUS_PLATFORM_WINDOWS

ImageDescriptor LoadImageFromPath(LPDIRECT3DDEVICE9 *pDevice, std::string_view path, int width, int height) {
    ImageDescriptor result;

    result.filepath = path;
    result.height = height;
    result.width = width;
    result.textureId = nullptr;

    HRESULT resultCode = D3DXCreateTextureFromFileEx(*pDevice, path.data(), width, height, D3DX_DEFAULT,
                                                     0,
                                                     D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT /*filer here*/,
                                                     D3DX_DEFAULT, 0, NULL,
                                                     NULL, reinterpret_cast<LPDIRECT3DTEXTURE9 *>(&result.textureId));

    if (resultCode != D3D_OK) {
        DS_ERROR("An error occurred during texture creation");
        switch (resultCode) {
            case D3DERR_INVALIDCALL: {
                DS_ERROR("Invalid call");
                break;
            }
            case D3DERR_NOTAVAILABLE: {
                DS_ERROR("Not available");
                break;
            }
            case D3DERR_OUTOFVIDEOMEMORY: {
                DS_ERROR("Out of video memory");
                break;
            }
            case D3DXERR_INVALIDDATA: {
                DS_ERROR("Invalid data");
                break;
            }
            case E_OUTOFMEMORY: {
                DS_ERROR("Out of memory");
                break;
            }
            default: {
                DS_ERROR("Unknown error");
            }
        }
        throw std::runtime_error("Cannot create texture from file");
    }

    return result;
}

#endif