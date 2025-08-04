#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>
#include <string>

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
inline const std::string PROJECT_MAIN = "main.lua";

#endif
