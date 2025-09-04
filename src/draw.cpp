#include "include/draw.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

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
    SDL_FRect dest{ std::round(position.x), std::round(position.y),
                    static_cast<float>(w),
                    static_cast<float>(h) };
    
    SDL_RenderTexture(renderer, texture, nullptr, &dest);

    SDL_DestroyTexture(texture);
}

void Draw::drawTriangle(Vector position1, Vector position2, Vector position3, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (position2.y < position1.y) std::swap(position1, position2);
    if (position3.y < position1.y) std::swap(position1, position3);
    if (position3.y < position2.y) std::swap(position2, position3);

    auto edgeInterp = [](Vector a, Vector b, float y) {
        if (a.y == b.y) return a.x;
        return a.x + (b.x - a.x) * ((y - a.y) / (b.y - a.y));
    };

    for (int y = (int)std::ceil(position1.y); y <= (int)std::floor(position3.y); y++) {
        bool secondHalf = (y > position2.y) || (position2.y == position1.y);

        float xa = edgeInterp(position1, position3, (float)y);
        float xb = secondHalf ? edgeInterp(position2, position3, (float)y) : edgeInterp(position1, position2, (float)y);

        if (xa > xb) std::swap(xa, xb);

        SDL_RenderLine(renderer, (int)std::ceil(xa), y, (int)std::floor(xb), y);
    }
}

void Draw::drawTriangleGPU(Vector position1, Vector position2, Vector position3, Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);

    SDL_Vertex verts[3];
    verts[0].position = { position1.x, position1.y };
    verts[1].position = { position2.x, position2.y };
    verts[2].position = { position3.x, position3.y };

    for (int i = 0; i < 3; i++) {
        verts[i].color = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
        verts[i].tex_coord = { 0.0f, 0.0f };
    }

    SDL_RenderGeometry(renderer, nullptr, verts, 3, nullptr, 0);
}

Color Draw::readPixel(Vector position) {
    SDL_Rect pixelRect;
    pixelRect.x = position.x;
    pixelRect.y = position.y;
    pixelRect.w = 1;
    pixelRect.h = 1;

    SDL_Surface* pixelSurface = SDL_RenderReadPixels(renderer, &pixelRect);

    Uint8 r, g, b, a;
    SDL_ReadSurfacePixel(pixelSurface, 0, 0, &r, &g, &b, &a);
    return Color(r, g, b, a);
}


void Draw::clearScreen(Color color) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

Draw drawObject;