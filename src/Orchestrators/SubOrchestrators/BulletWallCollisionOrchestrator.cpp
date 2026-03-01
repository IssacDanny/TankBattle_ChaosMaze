#include "Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.hpp"

// Helper remains internal to the .cpp
static Vector2D calculateMinimumTranslationVector(const AABB& moving, const AABB& stationary) {
    const float overlapLeft   = (moving.x + moving.width) - stationary.x;
    const float overlapRight  = (stationary.x + stationary.width) - moving.x;
    const float overlapTop    = (moving.y + moving.height) - stationary.y;
    const float overlapBottom = (stationary.y + stationary.height) - moving.y;

    if (overlapLeft <= overlapRight && overlapLeft <= overlapTop && overlapLeft <= overlapBottom) return { -overlapLeft, 0.0f };
    if (overlapRight <= overlapLeft && overlapRight <= overlapTop && overlapRight <= overlapBottom) return { overlapRight, 0.0f };
    if (overlapTop <= overlapLeft && overlapTop <= overlapRight && overlapTop <= overlapBottom) return { 0.0f, -overlapTop };
    return { 0.0f, overlapBottom };
}

void BulletWallCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    const ReflectionTransformer& reflectionMath,
    const BulletData& bulletData, // Use this for reading
    BulletMutator& bulletMutator, // Use this for writing
    const LevelData& level)
{
    if (!bulletData.isActive) return;

    for (const AABB& wall : level.walls) {
        if (!collisionMath.isIntersecting(bulletData.boundingBox, wall)) continue;

        // 1) Determine the impacted face
        const Vector2D n = collisionMath.calculateSurfaceNormal(bulletData.boundingBox, wall);

        // 2) Reflect velocity using the data's current velocity
        const Vector2D reflected = reflectionMath.calculateReflection(bulletData.velocity, n);
        bulletMutator.setVelocity(reflected);

        // 3) Push bullet out of the wall
        const Vector2D mtv = calculateMinimumTranslationVector(bulletData.boundingBox, wall);
        bulletMutator.applyDisplacement(mtv);

        break; // One bounce per frame
    }
}