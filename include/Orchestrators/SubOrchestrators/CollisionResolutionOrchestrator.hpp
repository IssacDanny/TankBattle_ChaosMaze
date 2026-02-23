#pragma once
#include <vector>
#include "Transformers/CollisionTransformer.hpp"
#include "Transformers/ReflectionTransformer.hpp"
#include "Mutators/TankMutator.hpp"
#include "Mutators/BulletMutator.hpp"
#include "Ledgers/EntityData.hpp"


#include "Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.hpp"

class CollisionResolutionOrchestrator {
private:
    TankWallCollisionOrchestrator   tankWallResolver;
    BulletWallCollisionOrchestrator bulletWallResolver;
    BulletTankCollisionOrchestrator bulletTankResolver;

public:
    /**
     * @brief The primary entry point for resolving all physical conflicts in the world.
     * 
     * This method orchestrates the sequence of collision checks:
     * 1. Tanks vs. Walls (Blocking)
     * 2. Bullets vs. Walls (Bouncing)
     * 3. Bullets vs. Tanks (Damage)
     * 
     * @param collisionMath Pure transformer for intersection logic.
     * @param reflectionMath Pure transformer for bouncing physics.
     * @param p1Mutator Agent for Player 1's state.
     * @param p2Mutator Agent for Player 2's state.
     * @param bulletMutators A collection of agents for all active projectiles.
     * @param level The static environment data (walls).
     */
    void execute(const CollisionTransformer& collisionMath, 
              const ReflectionTransformer& reflectionMath,
              TankMutator& p1Mutator, 
              TankMutator& p2Mutator, 
              std::vector<BulletMutator>& bulletMutators, 
              const LevelData& level);
};