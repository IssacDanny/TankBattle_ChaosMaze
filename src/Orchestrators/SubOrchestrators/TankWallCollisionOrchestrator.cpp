#include "Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.hpp"
#include <algorithm>

static Vector2D calculateMinimumTranslationVector(const AABB& moving, const AABB& stationary) {
    const float overlapLeft = (moving.x + moving.width) - stationary.x;
    const float overlapRight = (stationary.x + stationary.width) - moving.x;
    const float overlapTop = (moving.y + moving.height) - stationary.y;
    const float overlapBottom = (stationary.y + stationary.height) - moving.y;

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

void TankWallCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    const TankData& tankData, // The Spectacles
    TankMutator& tankMutator, // The Pen
    const LevelData& level)
{
    for (const AABB& wall : level.walls) {
        // We read from the Data, NOT the Mutator!
        const AABB& tankBox = tankData.boundingBox;

        if (!collisionMath.isIntersecting(tankBox, wall)) {
            continue;
        }

        // Compute the shortest correction vector and push the tank out of the wall.
        const Vector2D mtv = calculateMinimumTranslationVector(tankBox, wall);
        tankMutator.applyDisplacement(mtv);
    }
}