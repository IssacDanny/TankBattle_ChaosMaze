// Developer A: Conflict-resolution chain coordinator
#define private public
#include "Mutators/BulletMutator.hpp"
#include "Mutators/TankMutator.hpp"
#undef private

#include "Orchestrators/SubOrchestrators/CollisionResolutionOrchestrator.hpp"

/**
 * @brief Coordinates the three phases of collision: Tank-Wall, Bullet-Wall, and Bullet-Tank.
 * @param collisionMath Pure transformer for intersection checks.
 * @param reflectionMath Pure transformer for bouncing calculations.
 * @param p1Mutator Agent for Player 1.
 * @param p2Mutator Agent for Player 2.
 * @param bulletMutators List of agents for all active projectiles.
 * @param level The static environment data.
 */
void CollisionResolutionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    const ReflectionTransformer& reflectionMath,
    TankMutator& p1Mutator,
    TankMutator& p2Mutator,
    std::vector<BulletMutator>& bulletMutators,
    const LevelData& level)
{
    // Phase 1: Tanks vs. Walls (Blocking)
    tankWallResolver.execute(collisionMath, p1Mutator, level);
    tankWallResolver.execute(collisionMath, p2Mutator, level);

    // Phase 2 & 3: Bullets vs. Walls (Bouncing), then Bullets vs. Tanks (Damage)
    for (BulletMutator& bullet : bulletMutators) {
        if (!bullet.target.isActive) continue;

        // Phase 2: wall bounce
        bulletWallResolver.execute(collisionMath, reflectionMath, bullet, level);
        if (!bullet.target.isActive) continue;

        // Phase 3: damage (no self-inflicted damage)
        // Assumption from design: ownerID == 1 for Player 1 bullets, ownerID == 2 for Player 2 bullets.
        if (bullet.target.ownerID == 1) {
            bulletTankResolver.execute(collisionMath, bullet, p2Mutator);
        }
        else if (bullet.target.ownerID == 2) {
            bulletTankResolver.execute(collisionMath, bullet, p1Mutator);
        }
        else {
            // Fallback: if ownerID is not recognised, allow hits on both tanks
            // (This preserves gameplay rather than silently disabling damage.)
            bulletTankResolver.execute(collisionMath, bullet, p1Mutator);
            if (bullet.target.isActive) {
                bulletTankResolver.execute(collisionMath, bullet, p2Mutator);
            }
        }
    }
}
