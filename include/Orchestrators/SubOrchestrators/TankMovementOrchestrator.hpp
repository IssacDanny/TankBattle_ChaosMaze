#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Transformers/KinematicsTransformer.hpp"
#include "Mutators/TankMutator.hpp"

class TankMovementOrchestrator {
public:
    /**
     * @brief Orchestrates the movement of a single tank.
     * @param input The specific input state for this player (const)
     * @param time The current time ledger for delta time (const)
     * @param kinematics The mathematician for trig calculations (const)
     * @param mutator The agent authorised to move the tank
     */
    void execute(const InputLedger::PlayerInput& input, 
              const TimeLedger& time, 
              const KinematicsTransformer& kinematics, 
              const TankData& currentTankState,
              TankMutator& mutator);
};