#include "include/globals.h"

#include "include/load.h"

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 64;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 1080;

const std::string WINDOW_TITLE = "4Kiwi";
const std::string WINDOW_ICON = "assets/icon.png";

const std::string PROJECT_PATH = "project/";
const std::string EXTRA_PATH = "extra/";
const std::string PROJECT_MAIN = "main.lua";

std::string DEFAULT_FONT_PATH = "extra/kiwi4.ttf";
int DEFAULT_FONT_SIZE = 5;
Color DEFAULT_FONT_COLOR = Color(255, 255, 255, 255);
int DEFAULT_FONT = 0;

std::string DEFAULT_TEXTURE_PATH = "extra/kiwi4.png";
int DEFAULT_TEXTURE = 0;

void LoadDefaultAssets() {
    DEFAULT_FONT = Load::loadFont(DEFAULT_FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    DEFAULT_TEXTURE = Load::loadImage(DEFAULT_TEXTURE_PATH.c_str());
}
