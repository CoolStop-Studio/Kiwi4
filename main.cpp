#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sol/sol.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <filesystem>

#include <include/color.h>
#include <include/draw.h>
#include <include/globals.h>
#include <include/input.h>
#include <include/load.h>
#include <include/vector.h>

const int MAX_FPS = 200;
bool quit = false;

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
SDL_Texture* screenTexture = nullptr;

sol::state lua;

void bind_lua() {
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::math, sol::lib::package);
    
    lua["package"]["path"] = PROJECT_PATH + "?.lua;" + lua["package"]["path"].get<std::string>();

    lua.new_usertype<Load>("Load",
        "loadImage", &Load::loadImage,
        "loadFont", &Load::loadFont
    );

    lua.new_usertype<Color>("Color",
        sol::call_constructor, sol::constructors<Color(uint8_t, uint8_t, uint8_t, uint8_t)>(),
        "r", &Color::r,
        "g", &Color::g,
        "b", &Color::b,
        "a", &Color::a
    );

    lua.new_usertype<Draw>("Draw",
        "drawPixel", &Draw::drawPixel,
        "drawLine", &Draw::drawLine,
        "drawRect", &Draw::drawRect,
        "drawImage", [](Vector position1, Vector position2, sol::optional<int> textureID) {
            drawObject.drawImage(
                position1,
                position2,
                textureID.value_or(DEFAULT_TEXTURE)
            );
        },
        "drawText", [](const std::string& text, Vector position, sol::optional<Color> color,
                    sol::optional<int> fontID) {
            drawObject.drawText(
                text,
                position,
                color.value_or(DEFAULT_FONT_COLOR),
                fontID.value_or(DEFAULT_FONT)
            );
        },
        "clearScreen", &Draw::clearScreen
    );

    lua.new_usertype<Input>("Input",
        "isKeyPressed", &Input::isKeyPressed,
        "isKeyJustPressed", &Input::isKeyJustPressed,
        "isKeyJustReleased", &Input::isKeyJustReleased,
        "getLastKeyPressed", &Input::getLastKeyPressed,
        "getMousePosition", &Input::getMousePosition,
        "isMouseInRect", [](Vector position1, Vector position2, sol::optional<bool> inclusive) {
            return inputObject.isMouseInRect(
                position1,
                position2,
                inclusive.value_or(true)
            );
        }
    );

    auto vec_mul_vec = static_cast<Vector(Vector::*)(const Vector&) const>(&Vector::operator*);
    auto vec_mul_float = static_cast<Vector(Vector::*)(float) const>(&Vector::operator*);
    auto vec_div_vec = static_cast<Vector(Vector::*)(const Vector&) const>(&Vector::operator/);
    auto vec_div_float = static_cast<Vector(Vector::*)(float) const>(&Vector::operator/);

    lua.new_usertype<Vector>("Vector",
        sol::call_constructor, sol::constructors<Vector(float, float)>(),
        "x", &Vector::x,
        "y", &Vector::y,
        sol::meta_function::addition, &Vector::operator+,
        sol::meta_function::subtraction, &Vector::operator-,
        sol::meta_function::multiplication, sol::overload(
            vec_mul_vec,
            vec_mul_float,
            [](float scalar, const Vector& v) { return scalar * v; }  // float * Vector
        ),
        sol::meta_function::division, sol::overload(
            vec_div_vec,
            vec_div_float
        )
    );

    lua["Draw"] = &drawObject;
    lua["Input"] = &inputObject;

    lua.script_file((PROJECT_PATH + PROJECT_MAIN).c_str());

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
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    LoadDefaultAssets();

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_RESIZABLE);


    renderer = SDL_CreateRenderer(window, nullptr);


    screenTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );
    SDL_SetTextureScaleMode(screenTexture, SDL_SCALEMODE_NEAREST);

    fprintf(stdout, "Running...\n");

    bind_lua();

    const double targetFrameTime = 1.0 / MAX_FPS; 

    Uint64 last_tick = SDL_GetPerformanceCounter();
    Uint64 currentTick;
    Uint64 frameStartTick;

    double deltaTime = 0.0;
    double performanceFrequency = (double)SDL_GetPerformanceFrequency();

    std::string scriptPath = PROJECT_PATH + PROJECT_MAIN;
    auto lastWriteTime = std::filesystem::last_write_time(scriptPath);
    
    while (!quit) {
        frameStartTick = SDL_GetPerformanceCounter();
        currentTick = SDL_GetPerformanceCounter();

        deltaTime = (double)(currentTick - last_tick) / performanceFrequency;
        frameStartTick = currentTick;
        last_tick = currentTick;

        // --- Reload Script ---
        auto currentWriteTime = std::filesystem::last_write_time(scriptPath);
        if (currentWriteTime != lastWriteTime) {
            lastWriteTime = currentWriteTime;
            try {
                lua.script_file(scriptPath);
                std::cout << "[Lua] Script reloaded!\n";
            } catch (const sol::error& e) {
                std::cerr << "[Lua] Reload error: " << e.what() << "\n";
            }
        }


        // --- Update ---
        sol::function update = lua["_update"];

        if (update.valid()) {
            update(deltaTime);
        }

        render();

        handleEvents();




        // --- FPS Limiting ---
        Uint64 frameEndTick = SDL_GetPerformanceCounter();
        double frameTimeTaken = (double)(frameEndTick - frameStartTick) / performanceFrequency;

        double timeToWait = targetFrameTime - frameTimeTaken;

        if (timeToWait > 0) {
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

std::string formatPath(std::string& path) {
     if (!path.empty() && path[0] == '/') {
        path.erase(0, 1);
    }
    
    // If path starts with PROJECT_PATH -> return as is
    if (path.rfind(PROJECT_PATH, 0) == 0) {
        return path;
    }

    // If path starts with EXTRA_PATH -> return as is
    if (path.rfind(EXTRA_PATH, 0) == 0) {
        return path;
    }

    // Otherwise, prepend PROJECT_PATH
    return PROJECT_PATH + path;
}