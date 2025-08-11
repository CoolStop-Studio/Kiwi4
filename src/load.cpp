#include "include/load.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <cmath>
#include <vector>

#include "include/color.h"
#include "include/globals.h"
#include "include/utils.h"
#include "include/vector.h"

std::vector<SDL_Texture*> loaded_textures;
std::vector<TTF_Font*> loaded_fonts;

int Load::loadImage(std::string filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, formatPath(filePath).c_str());
    loaded_textures.push_back(texture);
    return loaded_textures.size() - 1;
}

int Load::loadFont(std::string filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(formatPath(filePath).c_str(), fontSize);
    loaded_fonts.push_back(font);
    return loaded_fonts.size() - 1;
}