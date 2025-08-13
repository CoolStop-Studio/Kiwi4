#ifndef LOAD_H
#define LOAD_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <string>
#include <vector>

extern std::vector<SDL_Texture*> loaded_textures;
extern std::vector<TTF_Font*> loaded_fonts;

struct Load {
    static int loadImage(std::string filePath);
    static int loadFont(std::string filePath, int fontSize);
};

extern Load loadObject;

#endif