#pragma once
#include "Ledgers/Vector2D.hpp"
#include "Ledgers/AABB.hpp"

class VisualTransformTransformer {
public:
    // Converts the physics engine's radians to the rendering engine's degrees
    float radiansToDegrees(float radians) const;

    // Calculates the exact centre of an AABB for proper sprite rotation
    Vector2D calculateCentre(const AABB& box) const;
};