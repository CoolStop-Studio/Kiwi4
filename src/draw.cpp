#include "include/draw.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <cmath>

#include "include/color.h"
#include "include/globals.h"
#include "include/load.h"
#include "include/utils.h"
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

void Draw::drawImage(Vector position1, Vector position2, int textureID) {
    SDL_SetRenderTarget(renderer, screenTexture);

    SDL_Texture* texture = loaded_textures[textureID];

    float x = std::round(std::min(position1.x, position2.x));
    float y = std::round(std::min(position1.y, position2.y));
    float w = std::round(std::fabs(position2.x - position1.x));
    float h = std::round(std::fabs(position2.y - position1.y));

    SDL_FRect dstRect = { x, y, w, h };

    SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}


void Draw::drawText(const std::string& text, Vector position, Color color, int fontID) {
    SDL_SetRenderTarget(renderer, screenTexture);

    if (text.empty()) {
        return; 
    }

    TTF_Font* font = loaded_fonts[fontID];

    SDL_Color sdlColor{ color.r, color.g, color.b, color.a };

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), sdlColor);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    SDL_FRect dest{ position.x, position.y,
                    static_cast<float>(w),
                    static_cast<float>(h) };
    
    SDL_RenderTexture(renderer, texture, nullptr, &dest);

    SDL_DestroyTexture(texture);
}

void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;