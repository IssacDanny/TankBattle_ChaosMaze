#pragma once
#include "Transformers/CollisionTransformer.hpp"
#include "Transformers/ReflectionTransformer.hpp"
#include "Mutators/BulletMutator.hpp"
#include "Ledgers/EntityData.hpp"

class BulletWallCollisionOrchestrator {
public:
    void execute(
        const CollisionTransformer& collisionMath, 
        const ReflectionTransformer& reflectionMath,
        const BulletData& bulletData,
        BulletMutator& bulletMutator,
        const LevelData& level);
};