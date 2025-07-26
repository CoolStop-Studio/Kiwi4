#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h>

const int FPS = 60;

int main(int argc, char* args[]) {
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

    // Main Event Loop
    SDL_Event event;
    bool quit = false;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    while (!quit) {
        float x, y;
        SDL_GetMouseState(&x, &y); // Get mouse pos

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Line
        SDL_RenderLine(renderer, 0, 0, x, y);

        SDL_RenderPresent(renderer);

        // Get inputs
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}