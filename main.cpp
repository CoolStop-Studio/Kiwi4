#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h> // For printf


int main(int argc, char* args[]) {
    // 1. Initialize SDL
    // SDL_INIT_VIDEO is typically needed for window creation.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1; // Exit if initialization fails
    }

    // Print compile-time SDL version (macros available in SDL3)
    printf("Compiled against SDL version %d.%d.%d\n",
           SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);

    // Get and print runtime SDL version
    // SDL_GetVersion() returns an integer, which is then parsed by macros.
    const int linked_version_int = SDL_GetVersion();
    printf("Linked against SDL version %d.%d.%d\n",
           SDL_VERSIONNUM_MAJOR(linked_version_int),
           SDL_VERSIONNUM_MINOR(linked_version_int),
           SDL_VERSIONNUM_MICRO(linked_version_int));

    // 2. Create a Window
    SDL_Window* window = SDL_CreateWindow("My SDL3 Window",  // Window title
                                          1920, 1080,             // Width, Height
                                          0);                   // Flags (0 for default behavior)

    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit(); // Clean up SDL if window creation fails
        return 1;   // Exit
    }

    // 3. Main Event Loop
    SDL_Event event; // Event handler
    bool quit = false; // Flag to control the loop

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    while (!quit) { // Loop until the 'quit' flag is true
        float x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background color
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Line color
        SDL_RenderLine(renderer, 0, 0, x, y);

        SDL_RenderPresent(renderer);

        // Process events from the event queue
        while (SDL_PollEvent(&event) != 0) {
            // Check the event type
            if (event.type == SDL_EVENT_QUIT) { // User requests to quit (e.g., clicks 'X')
                quit = true; // Set the flag to exit the main loop
            }
            // Add other event handling here (keyboard, mouse, etc.)
        }

        // 4. (Optional) Your Rendering Code Would Go Here
        // If you were rendering, you'd clear the renderer, draw, and then present.
        // For this example, we're just keeping the window open.

        // Add a small delay to prevent the loop from consuming too much CPU
        SDL_Delay(10); // Delays the execution for 10 milliseconds
    }

    // 5. Clean Up
    SDL_DestroyWindow(window); // Destroy the window
    SDL_Quit();                // Shut down SDL subsystems

    return 0; // Indicate successful execution
}