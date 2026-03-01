#include "Transformers/CollisionTransformer.hpp"
#include <algorithm>
#include <cmath>

/**
* @brief Standard AABB intersection check.
* @return True if the two boxes overlap.
*/
bool CollisionTransformer::isIntersecting(const AABB& a, const AABB& b) const
{
    // TODO: Implement the AABB overlap logic.
    // Check if (a.x < b.x + b.width) AND (a.x + a.width > b.x) ... and similarly for Y.

    bool overlapX = (a.x < b.x + b.width) && (a.x + a.width > b.x);
    bool overlapY = (a.y < b.y + b.height) && (a.y + a.height > b.y);

    return overlapX && overlapY;
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

    // Calculate penetration depths on all four sides
    float overlapLeft = (moving.x + moving.width) - stationary.x;
    float overlapRight = (stationary.x + stationary.width) - moving.x;
    float overlapTop = (moving.y + moving.height) - stationary.y;
    float overlapBottom = (stationary.y + stationary.height) - moving.y;

    // Find the minimum overlap to determine the collision axis
    float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

    // Return the surface normal based on which face had the shallowest penetration
    // Normal points outward from the stationary wall's surface
    if (minOverlap == overlapLeft) {
        return { -1.0f, 0.0f };  // Hit left face of stationary wall
    }
    else if (minOverlap == overlapRight) {
        return { 1.0f, 0.0f };   // Hit right face of stationary wall
    }
    else if (minOverlap == overlapTop) {
        return { 0.0f, -1.0f };  // Hit top face of stationary wall
    }
    else { // minOverlap == overlapBottom
        return { 0.0f, 1.0f };   // Hit bottom face of stationary wall
    }
}