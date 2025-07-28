#ifndef DRAW_H
#define DRAW_H

#include "include/color.h"
#include "include/draw.h"
#include "include/globals.h"
#include "include/vector.h"

// Declaration of the MyObject class
struct Draw {
    void drawPixel(Vector position, Color color); // Declaration of the member function
    void clearScreen(Color color);
};

// Declaration of the global object
// 'extern' keyword tells the compiler that 'object' exists
// somewhere else (in a .cpp file) and it will be linked later.
extern Draw drawObject;

#endif // MY_OBJECT_H