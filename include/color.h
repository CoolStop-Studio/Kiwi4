#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <string>
class Color {
public:
    uint8_t r, g, b, a;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    static Color HSV(float h, float s, float v, uint8_t a);
    static Color HEX(std::string code);
};

#endif
