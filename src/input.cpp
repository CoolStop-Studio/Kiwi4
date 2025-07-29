#include "include/input.h"
#include <string>

static const bool* newKeyState = nullptr;
static bool oldKeyState[SDL_SCANCODE_COUNT] = {false};
static int keyCount = SDL_SCANCODE_COUNT;

void updateInputState() {
    if (newKeyState) {
        SDL_memcpy(oldKeyState, newKeyState, keyCount);
    }

    newKeyState = SDL_GetKeyboardState(nullptr);
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

Input inputObject;
