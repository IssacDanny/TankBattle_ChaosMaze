#pragma once
#include <vector>
#include "Ledgers/GameLedgers.hpp" // Required for WorldLedger
#include "Transformers/CollisionTransformer.hpp"
#include "Transformers/ReflectionTransformer.hpp"
#include "Mutators/TankMutator.hpp"
#include "Mutators/BulletMutator.hpp"

// Sub-specialists
#include "Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.hpp"

class CollisionResolutionOrchestrator {
private:
    TankWallCollisionOrchestrator   tankWallResolver;
    BulletWallCollisionOrchestrator bulletWallResolver;
    BulletTankCollisionOrchestrator bulletTankResolver;

public:
    void execute(
        const CollisionTransformer& collisionMath, 
        const ReflectionTransformer& reflectionMath,
        const WorldLedger& world,
        TankMutator& p1Mutator, 
        TankMutator& p2Mutator, 
        std::vector<BulletMutator>& bulletMutators, 
        const LevelData& level);
};