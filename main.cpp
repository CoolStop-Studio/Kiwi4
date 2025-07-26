#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>

const int FPS = 60;
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
    Uint64 lastTick = SDL_GetPerformanceCounter();
    Uint64 currentTick;
    double deltaTime = 0.0;
    double performanceFrequency = (double)SDL_GetPerformanceFrequency();
    double maxFPS = 0.0;

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

    while (!quit) {
        currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)(currentTick - lastTick) / performanceFrequency;
        lastTick = currentTick;

        if ((1.0 / deltaTime) > maxFPS) {
            maxFPS = 1.0 / deltaTime;
        }
        std::cout << std::fixed << std::setprecision(2)
          << "FPS: " << (1.0 / deltaTime)
          << "   Max FPS: " << maxFPS << " \r" << std::flush;

        render(window, renderer, screenTexture);

        handleEvents(); 
    }

    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}