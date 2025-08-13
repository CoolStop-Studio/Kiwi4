#include "include/color.h"

#include <algorithm>
#include <cmath>
#include <string>

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r), g(g), b(b), a(a) {}



Color Color::HSV(float h, float s, float v, uint8_t a) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    float r_f, g_f, b_f;
    if (h < 60)      { r_f = c; g_f = x; b_f = 0; }
    else if (h < 120){ r_f = x; g_f = c; b_f = 0; }
    else if (h < 180){ r_f = 0; g_f = c; b_f = x; }
    else if (h < 240){ r_f = 0; g_f = x; b_f = c; }
    else if (h < 300){ r_f = x; g_f = 0; b_f = c; }
    else             { r_f = c; g_f = 0; b_f = x; }

    uint8_t r = static_cast<uint8_t>((r_f + m) * 255);
    uint8_t g = static_cast<uint8_t>((g_f + m) * 255);
    uint8_t b = static_cast<uint8_t>((b_f + m) * 255);

    return Color(r, g, b, a);
}

Color Color::HEX(std::string code) {
    // Remove #
    if (!code.empty() && code[0] == '#') {
        code.erase(0, 1);
    }

    uint8_t r = 0, g = 0, b = 0, a = 255;

    if (code.length() == 3) {
        r = std::stoi(std::string(2, code[0]), nullptr, 16);
        g = std::stoi(std::string(2, code[1]), nullptr, 16);
        b = std::stoi(std::string(2, code[2]), nullptr, 16);
    }
    else if (code.length() == 6) {
        r = std::stoi(code.substr(0,2), nullptr, 16);
        g = std::stoi(code.substr(2,2), nullptr, 16);
        b = std::stoi(code.substr(4,2), nullptr, 16);
    }
    else if (code.length() == 8) {
        r = std::stoi(code.substr(0,2), nullptr, 16);
        g = std::stoi(code.substr(2,2), nullptr, 16);
        b = std::stoi(code.substr(4,2), nullptr, 16);
        a = std::stoi(code.substr(6,2), nullptr, 16);
    }
    else {
        // not valid hex
        return Color(0,0,0,255);
    }

    return Color(r, g, b, a);
}