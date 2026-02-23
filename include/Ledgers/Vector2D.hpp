#pragma once
#include <cmath>

struct Vector2D {
    float x;
    float y;

    // --- The Vector Operators ---
    
    // Addition (v1 + v2)
    Vector2D operator+(const Vector2D& other) const {
        return { x + other.x, y + other.y };
    }

    // Subtraction (v1 - v2)
    Vector2D operator-(const Vector2D& other) const {
        return { x - other.x, y - other.y };
    }

    // Scalar Multiplication (v * 2.0f)
    Vector2D operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    // --- The Physics Essential Operators ---

    // Dot Product (Required for Reflection: v . n)
    float dot(const Vector2D& other) const {
        return (x * other.x) + (y * other.y);
    }

    // Magnitude (Length of the vector)
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalisation (Returns a unit vector of length 1)
    Vector2D normalize() const {
        float mag = magnitude();
        if (mag == 0.0f) return { 0.0f, 0.0f };
        return { x / mag, y / mag };
    }
};