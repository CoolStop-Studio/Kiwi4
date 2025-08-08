#include "include/input.h"

#include <string>
#include <cmath>

#include "include/globals.h"
#include "include/vector.h"


static const bool* newKeyState = nullptr;
static bool oldKeyState[SDL_SCANCODE_COUNT] = {0};
static int keyCount = SDL_SCANCODE_COUNT;
static SDL_Scancode lastKeyPressed = SDL_SCANCODE_UNKNOWN;

void updateInputState() {
    if (newKeyState) {
        SDL_memcpy(oldKeyState, newKeyState, keyCount);
    }

    newKeyState = SDL_GetKeyboardState(nullptr);

    for (int i = 0; i < keyCount; ++i) {
        if (newKeyState[i]) {
            lastKeyPressed = static_cast<SDL_Scancode>(i);
        }
    }
}



bool Input::isKeyPressed(std::string key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && newKeyState[scancode];
}

bool Input::isKeyJustPressed(std::string key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && (newKeyState[scancode] && !oldKeyState[scancode]);
}

bool Input::isKeyJustReleased(std::string key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && (!newKeyState[scancode] && oldKeyState[scancode]);
}

std::string Input::getLastKeyPressed() {
    if (lastKeyPressed == SDL_SCANCODE_UNKNOWN) {
        return "";
    }
    return SDL_GetScancodeName(lastKeyPressed);
}


Vector Input::getMousePosition() {
    float x, y;
    SDL_GetMouseState(&x, &y);
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    x /= ((float)width / (float)SCREEN_WIDTH);
    y /= ((float)height / (float)SCREEN_HEIGHT);

    
    return Vector(std::round(x - 0.5), std::round(y - 0.5));
}

Input inputObject;
