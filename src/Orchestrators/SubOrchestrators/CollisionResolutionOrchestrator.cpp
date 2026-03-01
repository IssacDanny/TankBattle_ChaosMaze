// Developer A: Conflict-resolution chain coordinator
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
    const WorldLedger& world,
    TankMutator& p1Mutator,
    TankMutator& p2Mutator,
    std::vector<BulletMutator>& bulletMutators,
    const LevelData& level)
{
    // Phase 1: Tanks vs. Walls
    tankWallResolver.execute(collisionMath, world.player1, p1Mutator, level);
    tankWallResolver.execute(collisionMath, world.player2, p2Mutator, level);

    // Phase 2 & 3: Bullets
    for (size_t i = 0; i < bulletMutators.size(); ++i) {
        const BulletData& bData = world.bulletPool[i];
        BulletMutator& bMutator = bulletMutators[i];

        if (!bData.isActive) continue;

        // Phase 2: Wall bounce
        bulletWallResolver.execute(collisionMath, reflectionMath, bData, bMutator, level);
        
        if (!bData.isActive) continue;

        // Phase 3: Damage (Logic based on ownerID)
        if (bData.ownerID == 1) {
            bulletTankResolver.execute(collisionMath, bData, bMutator, world.player2, p2Mutator);
        }
        else if (bData.ownerID == 2) {
            bulletTankResolver.execute(collisionMath, bData, bMutator, world.player1, p1Mutator);
        }
    }
}