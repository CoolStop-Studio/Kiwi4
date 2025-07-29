#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sol/sol.hpp>
#include <thread>
#include <chrono>

#include <include/color.h>
#include <include/draw.h>
#include <include/globals.h>
#include <include/input.h>
#include <include/vector.h>

const int MAX_FPS = 60;
bool quit = false;

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
SDL_Texture* screenTexture = nullptr;

sol::state lua;

void bind_lua() {
    fprintf(stderr, "Binding Lua...\n");
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::math);

    lua.new_usertype<Color>("Color",
        sol::call_constructor, sol::constructors<Color(uint8_t, uint8_t, uint8_t, uint8_t)>(),
        "r", &Color::r,
        "g", &Color::g,
        "b", &Color::b,
        "a", &Color::a
    );

    lua.new_usertype<Draw>("Draw",
        "drawPixel", &Draw::drawPixel,
        "clearScreen", &Draw::clearScreen
    );

    lua.new_usertype<Input>("Input",
        "isKeyPressed", &Input::isKeyPressed,
        "isKeyJustPressed", &Input::isKeyJustPressed,
        "isKeyJustReleased", &Input::isKeyJustReleased
    );

    lua.new_usertype<Vector>("Vector",
        sol::call_constructor, sol::constructors<Vector(float, float)>(),
        "x", &Vector::x,
        "y", &Vector::y
    );

    

    lua["Draw"] = &drawObject;
    lua["Input"] = &inputObject;

    lua.script_file("project/main.lua");

    sol::function init = lua["_init"];

    if (init.valid()) {
        init();
    }
}

void handleEvents() {
    updateInputState();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_EVENT_QUIT) {
            quit = true;
        }
    }
}

void render() {
    sol::function draw = lua["_draw"];

    if (draw.valid()) {
        draw();
    }

    // Render to the window
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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


    window = SDL_CreateWindow("4Kiwi",
                                          1080, 1080,  // Width, Height
                                          SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    screenTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        64, 64
    );
    SDL_SetTextureScaleMode(screenTexture, SDL_SCALEMODE_NEAREST);

    bind_lua();

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

        
        sol::function update = lua["_update"];

        if (update.valid()) {
            update(deltaTime);
        }


        render();

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