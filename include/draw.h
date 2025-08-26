#ifndef DRAW_H
#define DRAW_H

#include "include/color.h"
#include "include/draw.h"
#include "include/globals.h"
#include "include/vector.h"

struct Draw {
    static void drawPixel(Vector position, Color color);
    static void drawLine(Vector position1, Vector position2, Color color);
    static void drawRect(Vector position1, Vector position2, Color color);
    static void drawImage(Vector position1, Vector position2, int texture);
    static void drawText(const std::string& text, Vector position, Color color, int font);
    static void drawTriangle(Vector position1, Vector position2, Vector position3, Color color);
    static void clearScreen(Color color);
};

extern Draw drawObject;

#endif 