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
    TankMutator& mutator) 
{
    // TODO: Handle Body Rotation.
    // If 'left' is pressed, decrease the angle; if 'right', increase it.
    // Multiply by a rotation speed constant and time.deltaTime.
    // Command mutator.setBodyRotation().

    // TODO: Handle Forward/Backward Movement.
    // Determine the 'speed' based on 'up' or 'down' inputs.
    // Use kinematics.calculateDisplacement(speed, currentAngle, time.deltaTime).
    // Command mutator.applyDisplacement() with the resulting Vector2D.

    // TODO: Handle Independent Turret Rotation (Bonus).
    // If 'rotateTurretLeft/Right' keys are pressed, update the turretAngle.
    // Command mutator.setTurretRotation().
}