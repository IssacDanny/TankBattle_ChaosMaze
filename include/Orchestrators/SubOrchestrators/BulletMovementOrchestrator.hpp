#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Transformers/KinematicsTransformer.hpp"
#include "Mutators/BulletMutator.hpp"

class BulletMovementOrchestrator {
public:
    /**
     * @brief Orchestrates the linear movement of an active projectile.
     * @param time The current time ledger for delta time (const)
     * @param kinematics The mathematician for displacement calculations (const)
     * @param mutator The agent authorised to move the bullet
     */
    void execute(const TimeLedger& time, 
              const KinematicsTransformer& kinematics, 
              BulletMutator& mutator);
};