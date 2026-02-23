#pragma once
#include "Transformers/CollisionTransformer.hpp"
#include "Transformers/ReflectionTransformer.hpp"
#include "Mutators/BulletMutator.hpp"
#include "Ledgers/EntityData.hpp"

class BulletWallCollisionOrchestrator {
public:
    // Mediates the bouncing physics mandated by the specification
    void execute(const CollisionTransformer& collisionMath, 
              const ReflectionTransformer& reflectionMath,
              BulletMutator& bulletMutator, 
              const LevelData& level);
};