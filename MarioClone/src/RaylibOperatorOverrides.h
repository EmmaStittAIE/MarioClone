#pragma once

#include <iostream>
#include <stdexcept>

#include "raylib.h"
#include "raymath.h"

inline Vector2 operator+(const Vector2& a, const Vector2& b) { return Vector2Add(a, b); }

inline Vector2& operator+=(Vector2& a, const Vector2& b) {a = a + b;  return a; }

inline Vector2 operator-(Vector2 a) { return Vector2Negate(a); }

inline Vector2 operator-(Vector2& a) { return Vector2Negate(a); }

inline Vector2 operator-(const Vector2& a, const Vector2& b) { return Vector2Subtract(a, b); }

inline Vector2& operator-=(Vector2& a, const Vector2& b) { a = a - b; return a; }

inline Vector2 operator*(const Vector2& a, float b) { return Vector2Scale(a, b); }

inline Vector2& operator*=(Vector2& a, const float b) { a = a * b; return a; }

inline Vector2 operator/(const Vector2& a, const float b) {
    if (b == 0.0) {
        std::cerr << "Division by zero error." << std::endl;
        throw std::domain_error("Division by zero error");
    }
    float recip = 1.0 / b;
    return a * recip;
}

inline Vector2& operator/=(Vector2& a, const float b) { a = a / b; return a; }