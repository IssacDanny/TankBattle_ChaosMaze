#include "Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.hpp"

/**
 * @brief Registers hits on tanks and applies damage.
 * @param collisionMath Used to detect the hit.
 * @param bulletMutator The projectile agent (to be deactivated).
 * @param targetTankMutator The victim agent (to be damaged).
 */
void BulletTankCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath, 
    BulletMutator& bulletMutator, 
    TankMutator& targetTankMutator) 
{
    // TODO: Use collisionMath.isIntersecting() to check the bullet against the tank.
    // TODO: If a hit is confirmed:
    //   1. Command targetTankMutator.takeDamage().
    //   2. Command bulletMutator.deactivate() to remove it from the world.
}