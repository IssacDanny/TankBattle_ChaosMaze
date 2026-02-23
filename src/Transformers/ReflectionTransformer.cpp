#include "Transformers/ReflectionTransformer.hpp"

/**
 * @brief Calculates the bounce trajectory using the formula: V_new = V_old - 2(V_old . n)n
 * @param incidentVelocity The current velocity of the projectile (V_old).
 * @param surfaceNormal The normal vector of the wall (n).
 * @return The reflected velocity vector (V_new).
 */
Vector2D ReflectionTransformer::calculateReflection(const Vector2D& incidentVelocity, const Vector2D& surfaceNormal) const 
{
    // TODO: Calculate the dot product of incidentVelocity and surfaceNormal.
    // TODO: Apply the formula: V_new = V_old - (surfaceNormal * (2.0f * dotProduct)).
    // return V_new;
    return { 0.0f, 0.0f };
}