#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <string>

void updateInputState();

struct Input {
    static bool isKeyPressed(std::string key);
    static bool isKeyJustPressed(std::string key);
    static bool isKeyJustReleased(std::string key);
};

extern Input inputObject;

#endif