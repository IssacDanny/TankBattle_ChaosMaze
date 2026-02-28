// Developer A: Bullet-Wall collision reflection
#define private public
#include "Mutators/BulletMutator.hpp"
#undef private

#include "Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.hpp"

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

/**
 * @brief Handles the bouncing logic for projectiles striking walls.
 * @param collisionMath Used to find the surface normal of the impact.
 * @param reflectionMath Used to calculate the new velocity vector.
 * @param bulletMutator The agent whose velocity will be reflected.
 * @param level The collection of walls.
 */
void BulletWallCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    const ReflectionTransformer& reflectionMath,
    BulletMutator& bulletMutator,
    const LevelData& level)
{
    if (!bulletMutator.target.isActive) return;

    for (const AABB& wall : level.walls) {
        const AABB& bulletBox = bulletMutator.target.boundingBox;

        if (!collisionMath.isIntersecting(bulletBox, wall)) {
            continue;
        }

        // 1) Determine the impacted face (unit normal n)
        const Vector2D n = collisionMath.calculateSurfaceNormal(bulletBox, wall);

        // 2) Reflect velocity: V_new = V_old - 2(V_old·n)n
        const Vector2D reflected = reflectionMath.calculateReflection(bulletMutator.target.velocity, n);
        bulletMutator.setVelocity(reflected);

        // 3) Small correction: push bullet out of the wall to avoid "sticking"
        const Vector2D mtv = calculateMinimumTranslationVector(bulletBox, wall);
        bulletMutator.applyDisplacement(mtv);

        // One bounce per bullet per frame to avoid multiple reflections in a single update step.
        break;
    }
}
