#include "Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.hpp"

void BulletTankCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath,
    const BulletData& bulletData,
    BulletMutator& bulletMutator,
    const TankData& tankData,
    TankMutator& tankMutator)
{
    // We read from the 'bulletData' (Spectacles), not the mutator!
    if (!bulletData.isActive) return;

    if (!collisionMath.isIntersecting(bulletData.boundingBox, tankData.boundingBox)) {
        return;
    }

    // We use the Mutators only to write the changes
    tankMutator.takeDamage(1); 
    bulletMutator.deactivate();
}