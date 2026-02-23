#include "Transformers/CollisionTransformer.hpp"
#include <algorithm>

/**
 * @brief Standard AABB intersection check.
 * @return True if the two boxes overlap.
 */
bool CollisionTransformer::isIntersecting(const AABB& a, const AABB& b) const 
{
    // TODO: Implement the AABB overlap logic.
    // Check if (a.x < b.x + b.width) AND (a.x + a.width > b.x) ... and similarly for Y.
    return false;
}

/**
 * @brief Determines which face of the stationary box was struck.
 * @return A unit vector (normal) representing the direction of the wall's surface.
 */
Vector2D CollisionTransformer::calculateSurfaceNormal(const AABB& moving, const AABB& stationary) const 
{
    // TODO: Calculate the overlap distance on all four sides.
    // overlapLeft = (moving.x + moving.width) - stationary.x
    // overlapRight = (stationary.x + stationary.width) - moving.x
    // ... etc for Top and Bottom.

    // TODO: Find the smallest overlap. This indicates the axis of collision.
    // If overlapLeft is smallest, the normal is {-1.0f, 0.0f}.
    // If overlapTop is smallest, the normal is {0.0f, -1.0f}.
    return { 0.0f, 0.0f };
}