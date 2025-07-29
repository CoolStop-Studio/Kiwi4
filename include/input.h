#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <string>

#include "include/globals.h"
#include "include/vector.h"

void updateInputState();

struct Input {
    static bool isKeyPressed(std::string key);
    static bool isKeyJustPressed(std::string key);
    static bool isKeyJustReleased(std::string key);
    static Vector getMousePosition();
};

extern Input inputObject;

#endif