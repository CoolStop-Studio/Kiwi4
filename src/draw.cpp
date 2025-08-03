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

void Draw::drawRect(Vector position1, Vector position2, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);  // Set the render target
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);  // Set draw color

    float x = std::min(position1.x, position2.x);
    float y = std::min(position1.y, position2.y);
    float w = std::fabs(position2.x - position1.x) + 1.0f;
    float h = std::fabs(position2.y - position1.y) + 1.0f;

    SDL_FRect rect = { x, y, w, h };

    SDL_RenderFillRect(renderer, &rect);
}


void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;