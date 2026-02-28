// Developer A: Tank-Wall collision blocking
#define private public
#include "Mutators/TankMutator.hpp"
#undef private

#include "Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.hpp"

#include <algorithm>

static Vector2D calculateMinimumTranslationVector(const AABB& moving, const AABB& stationary) {
    // Positive overlap distances on each side (assumes intersection already confirmed).
    const float overlapLeft = (moving.x + moving.width) - stationary.x;
    const float overlapRight = (stationary.x + stationary.width) - moving.x;
    const float overlapTop = (moving.y + moving.height) - stationary.y;
    const float overlapBottom = (stationary.y + stationary.height) - moving.y;

    // Pick the shallowest penetration axis (robust comparisons, no float equality).
    if (overlapLeft <= overlapRight && overlapLeft <= overlapTop && overlapLeft <= overlapBottom) {
        return { -overlapLeft, 0.0f };
    }
    if (overlapRight <= overlapLeft && overlapRight <= overlapTop && overlapRight <= overlapBottom) {
        return { overlapRight, 0.0f };
    }
    if (overlapTop <= overlapLeft && overlapTop <= overlapRight && overlapTop <= overlapBottom) {
        return { 0.0f, -overlapTop };
    }
    return { 0.0f, overlapBottom };
}

/**
 * @brief Prevents tanks from entering wall geometry.
 * @param collisionMath Used to detect overlaps.
 * @param tankMutator The agent to be corrected if a collision occurs.
 * @param level The collection of walls to check against.
 */
void TankWallCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    TankMutator& tankMutator,
    const LevelData& level)
{
    for (const AABB& wall : level.walls) {
        const AABB& tankBox = tankMutator.target.boundingBox;

        if (!collisionMath.isIntersecting(tankBox, wall)) {
            continue;
        }

        // Compute the shortest correction vector and push the tank out of the wall.
        const Vector2D mtv = calculateMinimumTranslationVector(tankBox, wall);
        tankMutator.applyDisplacement(mtv);
    }
}
