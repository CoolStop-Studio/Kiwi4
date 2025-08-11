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
    if (text.empty()) {
        return; 
    }

    TTF_Font* font = loaded_fonts[fontID];

    if (!font) {
        SDL_Log("TTF_OpenFont error: %s", SDL_GetError());
        return;
    }

    SDL_Color sdlColor{ color.r, color.g, color.b, color.a };

    // length = 0 means 'text' is null-terminated
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), sdlColor);
    if (!surface) {
        SDL_Log("TTF_RenderText_Blended error: %s", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }  // :contentReference[oaicite:0]{index=0}

    // 3. Create a texture from that surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface error: %s", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }  // :contentReference[oaicite:1]{index=1}

    // 4. Query its size and render it
    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    SDL_FRect dest{ position.x, position.y,
                    static_cast<float>(w),
                    static_cast<float>(h) };
    SDL_RenderTexture(renderer, texture, nullptr, &dest);

    // 5. Clean up
    SDL_DestroyTexture(texture);
}

void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;