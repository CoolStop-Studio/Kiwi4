#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

#include "include/color.h"
#include "include/draw.h"

#include "include/globals.h"
#include "include/vector.h"

void Draw::drawPixel(Vector position, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, position.x, position.y);
}

void Draw::drawLine(Vector position1, Vector position2, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);  // Set the render target
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);  // Set draw color

    SDL_RenderLine(renderer,
        position1.x, position1.y,
        position2.x, position2.y
    );
}


void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;