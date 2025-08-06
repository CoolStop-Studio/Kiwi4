#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>
#include <string>

#include "include/vector.h"
#include "include/color.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Texture* screenTexture;

inline const int SCREEN_WIDTH = 64;
inline const int SCREEN_HEIGHT = 64;

inline const int WINDOW_WIDTH = 1080;
inline const int WINDOW_HEIGHT = 1080;

inline const std::string WINDOW_TITLE = "4Kiwi";
inline const std::string WINDOW_ICON = "assets/icon.png";

inline const std::string PROJECT_PATH = "project/";
inline const std::string EXTRA_PATH = "extra/";
inline const std::string PROJECT_MAIN = "main.lua";

inline const std::string DEFAULT_FONT_PATH = "extra/kiwi4.ttf";
inline const int DEFAULT_FONT_SIZE = 5;
inline const Color DEFAULT_FONT_COLOR = Color(255, 255, 255, 255);
inline const std::string DEFAULT_IMG_PATH = "extra/kiwi4.png";



#endif