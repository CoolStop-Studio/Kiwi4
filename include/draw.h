#ifndef DRAW_H
#define DRAW_H

#include "include/globals.h"
#include "include/vector.h"
#include "include/draw.h"

// Declaration of the MyObject class
struct Draw {
    void drawPixel(int x, int y); // Declaration of the member function
    void clearScreen();
};

// Declaration of the global object
// 'extern' keyword tells the compiler that 'object' exists
// somewhere else (in a .cpp file) and it will be linked later.
extern Draw object;

#endif // MY_OBJECT_H