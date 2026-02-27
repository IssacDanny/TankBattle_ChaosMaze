#include "Orchestrators/WorldUpdateOrchestrator.hpp"
#include "Mutators/TankMutator.hpp"
#include "Mutators/BulletMutator.hpp"

void WorldUpdateOrchestrator::execute(const TimeLedger& time, const InputLedger& input, WorldLedger& world) {
    
    // 1. Commission Mutators for the Combatants
    // These are our authorised agents for this frame's paperwork.
    TankMutator p1Mutator(world.player1);
    TankMutator p2Mutator(world.player2);

    // 2. Commission Mutators for the Munitions
    // We wrap the pre-allocated bullet pool in mutator agents.
    std::vector<BulletMutator> bulletMutators;
    for (auto& bullet : world.bulletPool) {
        bulletMutators.emplace_back(bullet);
    }

    // --- The Physic Simulation ---

    // Phase A: Locomotion
    // We delegate the movement of the tanks to the movement specialist.
    // Note how we only pass the relevant player's input to each call.
    tankMovement.execute(input.player1, time, kinematics, world.player1, p1Mutator);
    tankMovement.execute(input.player2, time, kinematics, world.player2, p2Mutator);

    // We move all active bullets currently in flight.
    for (size_t i = 0; i < world.bulletPool.size(); ++i) {
        bulletMovement.execute(
            time,
            kinematics,
            world.bulletPool[i],
            bulletMutators[i]
        );
    }

    // Phase B: Conflict Resolution
    // Now that everything has moved, we check for collisions and overlaps.
    // This specialist will handle blocking, bouncing, and damage.
    collisionResolution.execute(
        collisionMath, 
        reflectionMath, 
        p1Mutator, 
        p2Mutator, 
        bulletMutators, 
        world.maze
    );

    // Phase C: Housekeeping
    // We could handle cooldown reductions or temporary power-up timers here.
    p1Mutator.updateCooldown(time.deltaTime);
    p2Mutator.updateCooldown(time.deltaTime);
}