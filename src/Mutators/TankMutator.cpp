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
    target.position.x += delta.x;
    target.position.y += delta.y;

    // TODO: Synchronise the target.boundingBox.x and .y with the new position.
    target.boundingBox.x = target.position.x;
    target.boundingBox.y = target.position.y;
}

void TankMutator::setBodyRotation(float angleInRadians) 
{
    // TODO: Set target.bodyAngle to the provided value.
    target.bodyAngle = angleInRadians;
}

void TankMutator::takeDamage(int amount) 
{
    // TODO: Subtract amount from target.health.
    target.health -= static_cast<int>(amount);

    // TODO: If health falls below zero, ensure it stays at zero (or trigger destruction).
    if (target.health < 0) {
        target.health = 0;
    }
}

void TankMutator::updateCooldown(float deltaTime) 
{
    // TODO: If target.bulletCooldown is greater than zero, decrement it by deltaTime.
    if (target.bulletCooldown > 0) {
       target.bulletCooldown = static_cast<int>(target.bulletCooldown - (deltaTime * 60.0f)); 
    }
    if (target.bulletCooldown < 0) {
        target.bulletCooldown = 0;
    }
}

void TankMutator::setTurretRotation(float angleInRadians)
{
    target.turretAngle = angleInRadians;
}

void TankMutator::reset(const Vector2D& spawnPos, float initialAngle)
{
    target.position = spawnPos;
    target.bodyAngle = initialAngle;
    target.boundingBox.x = spawnPos.x;
    target.boundingBox.y = spawnPos.y;
    target.turretAngle = initialAngle; // Align turret with body on reset

	target.speed = 0; // Reset speed to stationary
    target.health = 100; // Reset health to full
    target.score = 0; // Reset score
    target.bulletCooldown = 0.0f; // Reset cooldown
}