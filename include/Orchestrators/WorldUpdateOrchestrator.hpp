#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Transformers/KinematicsTransformer.hpp"
#include "Transformers/CollisionTransformer.hpp"
#include "Transformers/ReflectionTransformer.hpp"
#include "Orchestrators/SubOrchestrators/TankMovementOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/BulletMovementOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/CollisionResolutionOrchestrator.hpp"

class WorldUpdateOrchestrator {
private:
    // Shared Transformers (Consolidated Resources)
    KinematicsTransformer kinematics;
    CollisionTransformer  collisionMath;
    ReflectionTransformer reflectionMath;

    // Subordinate Specialists
    TankMovementOrchestrator        tankMovement;
    BulletMovementOrchestrator      bulletMovement;
    CollisionResolutionOrchestrator collisionResolution;

public:
    /**
     * @brief Orchestrates the entire physics and logic update for the frame.
     */
    void execute(const TimeLedger& time, const InputLedger& input, WorldLedger& world);
};