#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sol/sol.hpp>
#include <thread>
#include <chrono>

const int MAX_FPS = 60;
bool quit = false;

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_EVENT_QUIT) {
            quit = true;
        }
    }
}

void render(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* screenTexture) {
    SDL_SetRenderTarget(renderer, screenTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Example pixel draw
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPoint(renderer, 10, 10);

    // Now render to the window
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Get window size
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    SDL_FRect dest = { 0, 0, (float)w, (float)h };
    SDL_RenderTexture(renderer, screenTexture, nullptr, &dest);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("4Kiwi",
                                          1080, 1080,  // Width, Height
                                          0);

    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Texture* screenTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        64, 64
    );
    SDL_SetTextureScaleMode(screenTexture, SDL_SCALEMODE_NEAREST);

    const double targetFrameTime = 1.0 / MAX_FPS; 

    Uint64 last_tick = SDL_GetPerformanceCounter();
    Uint64 currentTick;
    Uint64 frameStartTick;

    double deltaTime = 0.0;
    double performanceFrequency = (double)SDL_GetPerformanceFrequency();

    while (!quit) {
        frameStartTick = SDL_GetPerformanceCounter();
        currentTick = SDL_GetPerformanceCounter();

        deltaTime = (double)(currentTick - last_tick) / performanceFrequency;
        frameStartTick = currentTick;
        last_tick = currentTick;

        std::cout << std::fixed << std::setprecision(2)
          << "FPS: " << (1.0 / deltaTime) << " \r" << std::flush;

        render(window, renderer, screenTexture);

        handleEvents();





        // --- FPS Limiting Logic ---
        Uint64 frameEndTick = SDL_GetPerformanceCounter(); // Mark the end of the frame processing
        double frameTimeTaken = (double)(frameEndTick - frameStartTick) / performanceFrequency;

        double timeToWait = targetFrameTime - frameTimeTaken;

        if (timeToWait > 0) {
            // Convert seconds to milliseconds for std::this_thread::sleep_for
            // Add a small constant or use ceil if you want to ensure at least 1ms sleep
            long long millisecondsToWait = static_cast<long long>(timeToWait * 1000.0);

            if (millisecondsToWait > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToWait));
            }
        }
    }

    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}