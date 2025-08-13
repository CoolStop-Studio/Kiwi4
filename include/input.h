#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <string>

#include "include/vector.h"

void updateInputState();

struct Input {
    static bool isKeyPressed(std::string key);
    static bool isKeyJustPressed(std::string key);
    static bool isKeyJustReleased(std::string key);
    static std::string getLastKeyPressed();
    static Vector getMousePosition();
    static bool isMouseInRect(Vector position1, Vector position2, bool inclusive);
};

extern Input inputObject;

#endif