#include "include/globals.h"

#include "include/load.h"

#include <iostream>
#include <fstream>
#include <json/json.hpp>
using json = nlohmann::json;

int SCREEN_WIDTH = 64;
int SCREEN_HEIGHT = 64;

int WINDOW_WIDTH = 1080;
int WINDOW_HEIGHT = 1080;

std::string WINDOW_TITLE = "unknown";
std::string WINDOW_ICON = "";
std::string DEFAULT_ICON = "DEFAULT_ICON";

std::string JSON_PATH = "projects/project.json";
std::string PROJECT_PATH = "";
std::string EXTRA_PATH = "extra/";
std::string PROJECT_ENTRY = "";

int DEFAULT_TEXTURE = 0;
int DEFAULT_FONT = 0;
int DEFAULT_FONT_SIZE = 5;
Color DEFAULT_COLOR = Color(255, 255, 255, 255);

std::string DEFAULT_TEXTURE_NAME = "DEFAULT_TEXTURE";
std::string DEFAULT_FONT_NAME = "DEFAULT_FONT";

void loadConfig() {
    std::ifstream file(JSON_PATH);
    json projectjson;
    file >> projectjson;

    PROJECT_PATH = projectjson["path"];
    SCREEN_WIDTH = projectjson["window"]["width"];
    SCREEN_HEIGHT = projectjson["window"]["height"];
    WINDOW_TITLE = projectjson["window"]["title"];
    WINDOW_ICON = projectjson["window"]["icon"];
    PROJECT_ENTRY = projectjson["entry"];
}

void LoadDefaultAssets() {
    DEFAULT_TEXTURE = Load::loadImage(DEFAULT_TEXTURE_NAME);
    DEFAULT_FONT = Load::loadFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE);
}