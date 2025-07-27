#include <SDL3/SDL.h>
#include <iostream>

#include "include/globals.h"
#include "include/vector.h"
#include "include/draw.h"

// Definition of MyObject::myMethod
void Draw::drawPixel(int x,  int y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPoint(renderer, x, y);
}

void Draw::clearScreen() {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

Draw object;