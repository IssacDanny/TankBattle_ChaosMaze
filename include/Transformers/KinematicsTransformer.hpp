#pragma once
#include "Ledgers/Vector2D.hpp"

class KinematicsTransformer {
public:
    // Calculates the change in position (displacement) over a period of time
    Vector2D calculateDisplacement(float speed, float angleInRadians, float deltaTime) const;

    // Calculates a velocity vector from an angle and speed
    Vector2D calculateVelocity(float speed, float angleInRadians) const;
};