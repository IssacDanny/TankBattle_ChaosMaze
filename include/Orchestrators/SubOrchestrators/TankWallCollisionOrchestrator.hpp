#pragma once
#include "Transformers/CollisionTransformer.hpp"
#include "Mutators/TankMutator.hpp"
#include "Ledgers/EntityData.hpp"

class TankWallCollisionOrchestrator {
public:
    // Mediates the interaction between a tank and the maze boundaries
    void execute(
        const CollisionTransformer& collisionMath, 
        const TankData& tankData, // Second argument: Spectacles
        TankMutator& tankMutator, // Third argument: Pen
        const LevelData& level
    );
};