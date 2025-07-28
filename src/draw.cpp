#include <SDL3/SDL.h>
#include <iostream>

#include "include/color.h"
#include "include/draw.h"
#include "include/globals.h"
#include "include/vector.h"

// Definition of MyObject::myMethod
void Draw::drawPixel(Vector position, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, position.x, position.y);
}

void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;