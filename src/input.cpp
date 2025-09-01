#include "include/input.h"

#include <string>
#include <cmath>
#include <unordered_map>

#include "include/globals.h"
#include "include/vector.h"


static const bool* newKeyState = nullptr;
static bool oldKeyState[SDL_SCANCODE_COUNT] = {0};
static int keyCount = SDL_SCANCODE_COUNT;
static SDL_Scancode lastKeyPressed = SDL_SCANCODE_UNKNOWN;

Uint32 newMouseState = 0;
Uint32 oldMouseState = 0;
int lastMouseButton = 0;

static const std::unordered_map<std::string, Uint32> buttonNameToMask = {
    {"left",   SDL_BUTTON_LMASK},
    {"middle", SDL_BUTTON_MMASK},
    {"right",  SDL_BUTTON_RMASK}
};

static const std::unordered_map<Uint32, std::string> maskToButtonName = {
    {SDL_BUTTON_LMASK, "left"},
    {SDL_BUTTON_MMASK, "middle"},
    {SDL_BUTTON_RMASK, "right"}
};

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

    oldMouseState = newMouseState;
    newMouseState = SDL_GetMouseState(nullptr, nullptr);

    Uint32 changed = (newMouseState ^ oldMouseState);
    if (changed & newMouseState) { 
        if (newMouseState & SDL_BUTTON_LMASK) lastMouseButton = SDL_BUTTON_LEFT;
        if (newMouseState & SDL_BUTTON_MMASK) lastMouseButton = SDL_BUTTON_MIDDLE;
        if (newMouseState & SDL_BUTTON_RMASK) lastMouseButton = SDL_BUTTON_RIGHT;
    }
}



bool Input::isKeyPressed(const std::string& key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && newKeyState[scancode];
}

bool Input::isKeyJustPressed(const std::string& key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && (newKeyState[scancode] && !oldKeyState[scancode]);
}

bool Input::isKeyJustReleased(const std::string& key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key.c_str());
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return false;
    }
    return newKeyState && (!newKeyState[scancode] && oldKeyState[scancode]);
}

bool Input::isMousePressed(const std::string& button) {
    auto it = buttonNameToMask.find(button); // finds the mask in the map
    if (it == buttonNameToMask.end()) return false; // if the key doesnt exist, return false
    return (newMouseState & it->second) != 0; // returns if its pressed
}

bool Input::isMouseJustPressed(const std::string& button) {
    auto it = buttonNameToMask.find(button);
    if (it == buttonNameToMask.end()) return false;
    Uint32 mask = it->second;
    return ( (newMouseState & mask) && !(oldMouseState & mask) );
}

bool Input::isMouseJustReleased(const std::string& button) {
    auto it = buttonNameToMask.find(button);
    if (it == buttonNameToMask.end()) return false;
    Uint32 mask = it->second;
    return ( !(newMouseState & mask) && (oldMouseState & mask) );
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

bool Input::isMouseInRect(Vector position1, Vector position2, bool inclusive) {
    Vector mousePosition = Input::getMousePosition();
    if (inclusive) {
        return mousePosition.x >= position1.x && mousePosition.x <= position2.x && mousePosition.y >= position1.y && mousePosition.y <= position2.y;
    } else {
        return mousePosition.x > position1.x && mousePosition.x < position2.x && mousePosition.y > position1.y && mousePosition.y < position2.y;
    }
}

Input inputObject;
