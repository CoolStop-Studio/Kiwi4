#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
public:
    float x, y;

    Vector(float x = 0, float y = 0) : x(x), y(y) {}

    // Vector + Vector
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    // Vector - Vector
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    // Vector * Vector
    Vector operator*(const Vector& other) const {
        return Vector(x * other.x, y * other.y);
    }

    // Vector / Vector
    Vector operator/(const Vector& other) const {
        return Vector(x / other.x, y / other.y);
    }

    // Vector * float
    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // Vector / float
    Vector operator/(float scalar) const {
        return Vector(x / scalar, y / scalar);
    }
};

inline Vector operator*(float scalar, const Vector& v) {
    return Vector(v.x * scalar, v.y * scalar);
}

#endif