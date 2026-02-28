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

    // Step 1: Calculate dot product (V_old · n)
    float dotProduct = incidentVelocity.x * surfaceNormal.x + incidentVelocity.y * surfaceNormal.y;

    // Step 2: Apply reflection formula: V_new = V_old - 2(V_old · n)n
    float scale = 2.0f * dotProduct;

    Vector2D reflectedVelocity;
    reflectedVelocity.x = incidentVelocity.x - (surfaceNormal.x * scale);
    reflectedVelocity.y = incidentVelocity.y - (surfaceNormal.y * scale);

    return reflectedVelocity;
}