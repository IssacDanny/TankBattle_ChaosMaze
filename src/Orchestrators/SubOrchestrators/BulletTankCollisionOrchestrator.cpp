// Developer A: Bullet-Tank collision damage
#define private public
#include "Mutators/BulletMutator.hpp"
#include "Mutators/TankMutator.hpp"
#undef private

#include "Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.hpp"

static constexpr int kBulletDamage = 1;

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
    if (!bulletMutator.target.isActive) return;

    const AABB& bulletBox = bulletMutator.target.boundingBox;
    const AABB& tankBox = targetTankMutator.target.boundingBox;

    if (!collisionMath.isIntersecting(bulletBox, tankBox)) {
        return;
    }

    targetTankMutator.takeDamage(kBulletDamage);
    bulletMutator.deactivate();
}
