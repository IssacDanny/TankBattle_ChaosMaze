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
    // TODO: Phase 1 - Resolve Tank vs. Wall collisions for both players.
    // Call tankWallResolver.main() for p1Mutator and p2Mutator.

    // TODO: Phase 2 - Iterate through the bulletMutators.
    // For each bullet that is currently 'active':
    //   A. Resolve Bullet vs. Wall (Bouncing).
    //   B. Resolve Bullet vs. Tanks (Damage). 
    //      Note: Ensure a bullet does not damage its own creator (ownerID check).
}