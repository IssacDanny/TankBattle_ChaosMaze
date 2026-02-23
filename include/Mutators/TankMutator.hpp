#pragma once
#include "Ledgers/EntityData.hpp"

class TankMutator {
private:
    TankData& target; // The specific ledger entry this agent manages

public:
    // The constructor binds the mutator to a specific tank
    TankMutator(TankData& tank);

    // --- State Alteration Methods ---

    void applyDisplacement(const Vector2D& delta);
    void setBodyRotation(float angleInRadians);
    void setTurretRotation(float angleInRadians);
    
    void takeDamage(int amount);
    void updateCooldown(float deltaTime);
    
    // A helper to reset the tank to a spawn point
    void reset(const Vector2D& spawnPos, float initialAngle);
};