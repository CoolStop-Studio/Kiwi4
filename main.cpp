#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include <windows.h>
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
#include <include/files.h>
#include <include/globals.h>
#include <include/input.h>
#include <include/load.h>
#include <include/vector.h>

const int MAX_FPS = 400;
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
        sol::call_constructor,
        sol::factories([](uint8_t r, uint8_t g, uint8_t b, sol::optional<uint8_t> a) {
            return Color(r, g, b, a.value_or(255));
        }),
        "r", &Color::r,
        "g", &Color::g,
        "b", &Color::b,
        "a", &Color::a,

        "hsv", sol::factories([](float h, float s, float v, sol::optional<uint8_t> a) {
            return Color::HSV(h, s, v, a.value_or(255));
        }),
        "hex", sol::factories([](std::string code) {
            return Color::HEX(code);
        })
    );

    lua["Color"]["BLACK"]   = Color(0, 0, 0, 255);
    lua["Color"]["WHITE"]   = Color(255, 255, 255, 255);
    lua["Color"]["RED"]     = Color(255, 0, 0, 255);
    lua["Color"]["GREEN"]   = Color(0, 255, 0, 255);
    lua["Color"]["BLUE"]    = Color(0, 0, 255, 255);
    lua["Color"]["YELLOW"]  = Color(255, 255, 0, 255);
    lua["Color"]["CYAN"]    = Color(0, 255, 255, 255);
    lua["Color"]["MAGENTA"] = Color(255, 0, 255, 255);
    lua["Color"]["ORANGE"]  = Color(255, 128, 0, 255);
    lua["Color"]["PURPLE"]  = Color(128, 0, 128, 255);


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
                color.value_or(DEFAULT_COLOR),
                fontID.value_or(DEFAULT_FONT)
            );
        },
        "drawTriangle", &Draw::drawTriangle,
        "clearScreen", &Draw::clearScreen
    );

    lua.new_usertype<Files>("Files",
        "getFiles", &Files::getFiles,
        "getFolders", &Files::getFolders,
        "newFile", &Files::newFile,
        "newFolder", &Files::newFolder,
        "deleteFile", &Files::deleteFile,
        "deleteFolder", &Files::deleteFolder,
        "readFile", &Files::readFile,
        "writeFile", &Files::writeFile
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

    lua["Config"] = lua.create_table();
    lua["Config"]["window"] = lua.create_table_with(
        "width",  SCREEN_WIDTH,
        "height", SCREEN_HEIGHT,
        "size",   Vector(WINDOW_WIDTH, WINDOW_HEIGHT),
        "title",  WINDOW_TITLE,
        "icon",   WINDOW_ICON
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

    lua["Vector"]["UP"]    = Vector(0, -1);
    lua["Vector"]["DOWN"]  = Vector(0, 1);
    lua["Vector"]["LEFT"]  = Vector(-1, 0);
    lua["Vector"]["RIGHT"] = Vector(1, 0);

    lua["Draw"] = &drawObject;
    lua["Files"] = &filesObject;
    lua["Input"] = &inputObject;

    lua.script_file((PROJECT_PATH + PROJECT_ENTRY).c_str());

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

    // ::FreeConsole();

    loadConfig();

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_RESIZABLE);

    SDL_Surface* icon_surface = nullptr;
    if (WINDOW_ICON == DEFAULT_ICON) {
        icon_surface = Load::LoadEmbeddedSurface(DEFAULT_ICON.c_str());
    } else {
        icon_surface = IMG_Load(WINDOW_ICON.c_str());
    }
    SDL_SetWindowIcon(window, icon_surface);
    SDL_DestroySurface(icon_surface);



    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    screenTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );
    SDL_SetTextureScaleMode(screenTexture, SDL_SCALEMODE_NEAREST);

    fprintf(stdout, "Running...\n");

    LoadDefaultAssets();
    bind_lua();

    const double targetFrameTime = 1.0 / MAX_FPS; 

    Uint64 last_tick = SDL_GetPerformanceCounter();
    Uint64 currentTick;
    Uint64 frameStartTick;

    double deltaTime = 0.0;
    double performanceFrequency = (double)SDL_GetPerformanceFrequency();

    std::string scriptPath = PROJECT_PATH + PROJECT_ENTRY;
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