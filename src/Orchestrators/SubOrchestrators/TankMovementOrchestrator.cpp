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
	const TankData& currentTankState,
    TankMutator& mutator) 
{
    // TODO: Handle Body Rotation.
    // If 'left' is pressed, decrease the angle; if 'right', increase it.
    // Multiply by a rotation speed constant and time.deltaTime.
    // Command mutator.setBodyRotation().
	const float ROTATION_SPEED = 2.5f;
    float newTankAngle = currentTankState.bodyAngle;

    if (input.left)
        newTankAngle -= ROTATION_SPEED * time.deltaTime;
    if (input.right)
        newTankAngle += ROTATION_SPEED * time.deltaTime;

    mutator.setBodyRotation(newTankAngle);


    // TODO: Handle Forward/Backward Movement.
    // Determine the 'speed' based on 'up' or 'down' inputs.
    // Use kinematics.calculateDisplacement(speed, currentAngle, time.deltaTime).
    // Command mutator.applyDisplacement() with the resulting Vector2D.
    const float MOVE_SPEED = 100.0f;

    float speed = 0.0f;

    if (input.up)
        speed = MOVE_SPEED;
    else if (input.down)
        speed = -MOVE_SPEED;

    if (speed != 0.0f)
    {
        Vector2D movement = kinematics.calculateDisplacement(
            speed,
            newTankAngle,
            time.deltaTime);

        mutator.applyDisplacement(movement);
    }

    // TODO: Handle Independent Turret Rotation (Bonus).
    // If 'rotateTurretLeft/Right' keys are pressed, update the turretAngle.
    // Command mutator.setTurretRotation().
	float newTurretAngle = currentTankState.turretAngle;

    if (input.rotateTurretLeft) {
		newTurretAngle -= ROTATION_SPEED * time.deltaTime;
	}
    if (input.rotateTurretRight) {
		newTurretAngle += ROTATION_SPEED * time.deltaTime;
    }

	mutator.setTurretRotation(newTurretAngle);
}