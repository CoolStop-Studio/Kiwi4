#ifndef DRAW_H
#define DRAW_H

#include "include/color.h"
#include "include/draw.h"
#include "include/globals.h"
#include "include/vector.h"

// Declaration of the MyObject class
struct Draw {
    void drawPixel(Vector position, Color color);
    void drawLine(Vector position1, Vector position2, Color color);
    void drawRect(Vector position1, Vector position2, Color color);
    void drawImage(Vector position1, Vector position2, const std::string& filePath = DEFAULT_IMG_PATH);
    void drawText(const std::string& text, Vector position, Color color, const std::string& fontPath = DEFAULT_FONT_PATH, int fontSize = DEFAULT_FONT_SIZE);
    void clearScreen(Color color);
};

// Declaration of the global object
// 'extern' keyword tells the compiler that 'object' exists
// somewhere else (in a .cpp file) and it will be linked later.
extern Draw drawObject;

#endif // MY_OBJECT_H