#include "Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.hpp"

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
    // TODO: Iterate through level.walls.
    // TODO: If collisionMath.isIntersecting() is true for this bullet:
    //   1. Request the surface normal (n) from collisionMath.calculateSurfaceNormal().
    //   2. Pass the current velocity and normal to reflectionMath.calculateReflection().
    //   3. Command bulletMutator.setVelocity() with the resulting reflected vector.
    //   4. (Optional) Apply a small displacement to move the bullet slightly away from the wall 
    //      to prevent it from getting stuck inside the geometry.
}