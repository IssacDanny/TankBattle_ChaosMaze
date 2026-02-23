#include "Transformers/KinematicsTransformer.hpp"
#include <cmath>

/**
 * @brief Calculates the displacement vector for a given speed and angle.
 * @return A Vector2D representing the change in position.
 */
Vector2D KinematicsTransformer::calculateDisplacement(float speed, float angleInRadians, float deltaTime) const 
{
    // TODO: Calculate velocity components using trigonometry.
    // vx = speed * cos(angle)
    // vy = speed * sin(angle)
    
    // TODO: Multiply the velocity by deltaTime to get displacement.
    // return { vx * deltaTime, vy * deltaTime }
    return { 0.0, 0.0 };
}

/**
 * @brief Calculates a velocity vector from speed and angle.
 */
Vector2D KinematicsTransformer::calculateVelocity(float speed, float angleInRadians) const 
{
    // TODO: Return a Vector2D where x = speed * cos(angle) and y = speed * sin(angle).
    return { 0.0, 0.0 };
}