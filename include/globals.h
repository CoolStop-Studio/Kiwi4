#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "include/vector.h"
#include "include/color.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Texture* screenTexture;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const std::string WINDOW_TITLE;
extern const std::string WINDOW_ICON;

extern const std::string PROJECT_PATH;
extern const std::string EXTRA_PATH;
extern const std::string PROJECT_MAIN;

extern std::string DEFAULT_FONT_PATH;
extern int DEFAULT_FONT_SIZE;
extern Color DEFAULT_FONT_COLOR;
extern int DEFAULT_FONT;

extern std::string DEFAULT_TEXTURE_PATH;
extern int DEFAULT_TEXTURE;

void LoadDefaultAssets();

#endif
