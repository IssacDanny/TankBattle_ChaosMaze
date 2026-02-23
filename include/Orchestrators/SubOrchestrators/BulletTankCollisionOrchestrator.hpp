#pragma once
#include "Transformers/CollisionTransformer.hpp"
#include "Mutators/BulletMutator.hpp"
#include "Mutators/TankMutator.hpp"

class BulletTankCollisionOrchestrator {
public:
    // Mediates the interaction between a projectile and a combatant
    void execute(const CollisionTransformer& collisionMath, 
              BulletMutator& bulletMutator, 
              TankMutator& targetTankMutator);
};