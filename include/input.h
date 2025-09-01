#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <string>

#include "include/vector.h"

void updateInputState();

struct Input {
    static bool isKeyPressed(const std::string& key);
    static bool isKeyJustPressed(const std::string& key);
    static bool isKeyJustReleased(const std::string& key);
    static bool isMousePressed(const std::string& button);
    static bool isMouseJustPressed(const std::string& button);
    static bool isMouseJustReleased(const std::string& button);
    static std::string getLastKeyPressed();
    static Vector getMousePosition();
    static bool isMouseInRect(Vector position1, Vector position2, bool inclusive);
};

extern Input inputObject;

#endif