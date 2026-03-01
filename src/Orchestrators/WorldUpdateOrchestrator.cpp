#include "Orchestrators/WorldUpdateOrchestrator.hpp"
#include "Mutators/TankMutator.hpp"
#include "Mutators/BulletMutator.hpp"

void WorldUpdateOrchestrator::execute(const TimeLedger& time, const InputLedger& input, WorldLedger& world) {
    
    // 1. Commission Mutators
    TankMutator p1Mutator(world.player1);
    TankMutator p2Mutator(world.player2);
    std::vector<BulletMutator> bulletMutators;
    for (auto& bullet : world.bulletPool) {
        bulletMutators.emplace_back(bullet);
    }

    // --- Phase A: Locomotion ---
    tankMovement.execute(input.player1, time, kinematics, world.player1, p1Mutator);
    tankMovement.execute(input.player2, time, kinematics, world.player2, p2Mutator);

    // --- Phase B: Ballistic Aging (The Lifespan Logic) ---
    for (size_t i = 0; i < world.bulletPool.size(); ++i) {
        if (world.bulletPool[i].isActive) {
            // Reduce lifespan by delta time
            world.bulletPool[i].lifespan -= time.deltaTime;
            
            // If the round has expired (e.g., after 5 seconds), retire it
            if (world.bulletPool[i].lifespan <= 0.0f) {
                bulletMutators[i].deactivate();
            }
        }
    }

    // --- Phase C: Weaponry (The Regulated Firing) ---
    auto fireWeapon = [&](const InputLedger::PlayerInput& pInput, TankData& tank, int ownerID) {
        if (pInput.shoot && tank.bulletCooldown <= 0) {
            
            // Census: Count only active bullets belonging to THIS owner
            int activeCount = 0;
            for (const auto& b : world.bulletPool) {
                if (b.isActive && b.ownerID == ownerID) activeCount++;
            }

            if (activeCount < 5) {
                for (size_t i = 0; i < world.bulletPool.size(); ++i) {
                    if (!world.bulletPool[i].isActive) {
                        // Calculate spawn...
                        Vector2D center = { tank.boundingBox.x + 16.0f, tank.boundingBox.y + 16.0f };
                        Vector2D vel = kinematics.calculateVelocity(400.0f, tank.turretAngle);
                        Vector2D offset = kinematics.calculateVelocity(24.0f, tank.turretAngle);
                        Vector2D spawnPos = { center.x + offset.x - 4.0f, center.y + offset.y - 4.0f }; 

                        // Fire and set a 5-second lifespan
                        bulletMutators[i].spawn(spawnPos, vel, ownerID);
                        world.bulletPool[i].lifespan = 5.0f; 
                        
                        tank.bulletCooldown = 20; 
                        break; 
                    }
                }
            }
        }
    };

    fireWeapon(input.player1, world.player1, 1);
    fireWeapon(input.player2, world.player2, 2);

    // --- Phase D: Ballistic Advancement ---
    for (size_t i = 0; i < world.bulletPool.size(); ++i) {
        if (world.bulletPool[i].isActive) {
            bulletMovement.execute(time, kinematics, world.bulletPool[i], bulletMutators[i]);
        }
    }

    // --- Phase E: Conflict Resolution & Housekeeping ---
    collisionResolution.execute(collisionMath, reflectionMath, world, p1Mutator, p2Mutator, bulletMutators, world.maze);
    p1Mutator.updateCooldown(time.deltaTime);
    p2Mutator.updateCooldown(time.deltaTime);
}