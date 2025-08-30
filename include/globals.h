#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>
#include <string>
#include "include/vector.h"
#include "include/color.h"

// Renderer/Window
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Texture* screenTexture;

// Window properties (loaded from JSON)
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern std::string WINDOW_TITLE;
extern std::string WINDOW_ICON;
extern std::string DEFAULT_ICON;

// Project paths (loaded from JSON)
extern std::string JSON_PATH;
extern std::string PROJECT_PATH;
extern std::string EXTRA_PATH;
extern std::string PROJECT_ENTRY;

extern int DEFAULT_TEXTURE;
extern int DEFAULT_FONT;
extern int DEFAULT_FONT_SIZE;
extern Color DEFAULT_COLOR;

extern std::string DEFAULT_TEXTURE_NAME;
extern std::string DEFAULT_FONT_NAME;

// Asset loading
void LoadDefaultAssets();
void loadConfig();

#endif
