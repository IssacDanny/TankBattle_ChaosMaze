#include "Orchestrators/SubOrchestrators/TankMovementOrchestrator.hpp"

/**
 * @brief Translates player input into tank rotation and movement.
 * @param input The specific input state for the player being processed (const).
 * @param time The chronometer providing Delta Time (const).
 * @param kinematics The mathematician for trigonometric calculations (const).
 * @param mutator The agent authorised to alter the tank's ledger.
 */

void TankMovementOrchestrator::execute(
    const InputLedger::PlayerInput& input, 
    const TimeLedger& time, 
    const KinematicsTransformer& kinematics, 
    const TankData& tankData, 
    TankMutator& mutator) 
{
    // 1. Define the mechanical capabilities of the tank
    const float ROTATION_SPEED = 3.0f; // Radians per second
    const float MOVEMENT_SPEED = 150.0f; // Pixels per second

    float newBodyAngle = tankData.bodyAngle;
    float newTurretAngle = tankData.turretAngle;
    float rotationStep = ROTATION_SPEED * time.deltaTime;

    // 2. Handle Chassis Rotation (The turret must turn with the body!)
    if (input.left) {
        newBodyAngle -= rotationStep;
        newTurretAngle -= rotationStep; // Mechanical linkage
    }
    if (input.right) {
        newBodyAngle += rotationStep;
        newTurretAngle += rotationStep; // Mechanical linkage
    }

    // 3. Handle Independent Turret Rotation (The Bonus Feature)
    if (input.rotateTurretLeft) {
        newTurretAngle -= rotationStep;
    }
    if (input.rotateTurretRight) {
        newTurretAngle += rotationStep;
    }

    // Apply the calculated rotations to the ledger via the Mutator
    mutator.setBodyRotation(newBodyAngle);
    mutator.setTurretRotation(newTurretAngle);

    // 4. Handle Locomotion (Forward and Reverse)
    float currentSpeed = 0.0f;
    if (input.up) {
        currentSpeed = MOVEMENT_SPEED;
    } else if (input.down) {
        currentSpeed = -MOVEMENT_SPEED; // Reverse gear
    }

    // If the throttle is engaged, calculate and apply displacement
    if (currentSpeed != 0.0f) {
        Vector2D displacement = kinematics.calculateDisplacement(currentSpeed, newBodyAngle, time.deltaTime);
        mutator.applyDisplacement(displacement);
    }
}