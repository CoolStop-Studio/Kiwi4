#include "include/load.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>
#include <windows.h>

#include <iostream>
#include <cmath>
#include <vector>

#include "include/color.h"
#include "include/globals.h"
#include "include/utils.h"
#include "include/vector.h"

std::vector<SDL_Texture*> loaded_textures;
std::vector<TTF_Font*> loaded_fonts;

std::vector<unsigned char> LoadEmbeddedResource(const char* resName) {
    HRSRC hRes = FindResource(NULL, resName, RT_RCDATA);
    if (!hRes) return {};

    HGLOBAL hData = LoadResource(NULL, hRes);
    if (!hData) return {};

    DWORD size = SizeofResource(NULL, hRes);
    void* ptr = LockResource(hData);
    if (!ptr) return {};

    unsigned char* bytes = static_cast<unsigned char*>(ptr);
    return std::vector<unsigned char>(bytes, bytes + size);
}

static std::vector<std::vector<unsigned char>> embedded_font_buffers;

SDL_Texture* Load::LoadEmbeddedTexture(const char* resName) {
    std::vector<unsigned char> buffer = LoadEmbeddedResource(resName);
    if (buffer.empty()) return nullptr;

    SDL_IOStream* rw = SDL_IOFromConstMem(buffer.data(), (int)buffer.size());
    if (!rw) return nullptr;

    SDL_Texture* tex = IMG_LoadTexture_IO(renderer, rw, 1);
    return tex;
}

SDL_Surface* Load::LoadEmbeddedSurface(const char* resName) {
    std::vector<unsigned char> buffer = LoadEmbeddedResource(resName);
    if (buffer.empty()) return nullptr;

    SDL_IOStream* rw = SDL_IOFromConstMem(buffer.data(), (int)buffer.size());
    if (!rw) return nullptr;

    SDL_Surface* surface = IMG_Load_IO(rw, 1);
    return surface;
}


TTF_Font* Load::LoadEmbeddedFont(const char* resName, int ptsize) {
    std::vector<unsigned char> buffer = LoadEmbeddedResource(resName);
    if (buffer.empty()) return nullptr;

    embedded_font_buffers.push_back(buffer); // keep buffer alive
    std::vector<unsigned char>& stored = embedded_font_buffers.back();

    SDL_IOStream* rw = SDL_IOFromConstMem(stored.data(), (int)stored.size());
    if (!rw) return nullptr;

    TTF_Font* font = TTF_OpenFontIO(rw, 1, ptsize);
    if (!font) {
        SDL_Log("TTF_OpenFontIO failed: %s", SDL_GetError());
    }
    return font;
}


void Load::clearBuffers() {
    embedded_font_buffers.clear();
}








int Load::loadImage(std::string filePath) {
    SDL_Texture* texture = nullptr;

    if (filePath == DEFAULT_TEXTURE_NAME) {
        texture = LoadEmbeddedTexture("DEFAULT_TEXTURE");
    } else {
        texture = IMG_LoadTexture(renderer, formatPath(filePath).c_str());
    }

    loaded_textures.push_back(texture);
    return (int)loaded_textures.size() - 1;
}

int Load::loadFont(std::string filePath, int fontSize) {
    TTF_Font* font = nullptr;

    if (filePath == DEFAULT_FONT_NAME) {
        font = LoadEmbeddedFont("DEFAULT_FONT", DEFAULT_FONT_SIZE);
    } else {
        font = TTF_OpenFont(formatPath(filePath).c_str(), fontSize);
    }
    loaded_fonts.push_back(font);

    printf("font: %s, size: %d", filePath.c_str(), fontSize);
    return loaded_fonts.size() - 1;
}






