#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cstdint>

class Color {
public:
    uint8_t r, g, b, a;
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
};

#endif