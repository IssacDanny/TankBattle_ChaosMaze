#include "Mutators/TankMutator.hpp"

/**
 * @brief Binds the mutator to a specific tank ledger entry.
 */
TankMutator::TankMutator(TankData& tank) : target(tank) {}

/**
 * @brief Updates the tank's position and its physical collider.
 */
void TankMutator::applyDisplacement(const Vector2D& delta) 
{
    // TODO: Update target.position.x and .y by adding delta.x and .y.
    // TODO: Synchronise the target.boundingBox.x and .y with the new position.
}

void TankMutator::setBodyRotation(float angleInRadians) 
{
    // TODO: Set target.bodyAngle to the provided value.
}

void TankMutator::takeDamage(int amount) 
{
    // TODO: Subtract amount from target.health.
    // TODO: If health falls below zero, ensure it stays at zero (or trigger destruction).
}

void TankMutator::updateCooldown(float deltaTime) 
{
    // TODO: If target.bulletCooldown is greater than zero, decrement it by deltaTime.
}