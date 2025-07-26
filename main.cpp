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

void render(SDL_Renderer* renderer) {
    float x, y;
    SDL_GetMouseState(&x, &y); // Get mouse pos

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Line
    SDL_RenderLine(renderer, 0, 0, x, y);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Line
    SDL_RenderLine(renderer, 1920, 0, x, y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Line
    SDL_RenderLine(renderer, 1920, 1080, x, y);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Line
    SDL_RenderLine(renderer, 0, 1080, x, y);

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

    SDL_Window* window = SDL_CreateWindow("My SDL3 Window",
                                          1920, 1080,  // Width, Height
                                          0);

    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

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

        render(renderer);

        handleEvents(); 
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}