#include "Orchestrators/SubOrchestrators/BulletMovementOrchestrator.hpp"

/**
 * @brief Advances active projectiles along their current velocity vectors.
 * @param time The chronometer providing Delta Time (const).
 * @param kinematics The calculator for displacement calculations (const).
 * @param mutator The agent authorised to move the bullet.
 */
void BulletMovementOrchestrator::execute(
    const TimeLedger& time, 
    const KinematicsTransformer& kinematics, 
	const BulletData& bullet,
    BulletMutator& mutator) 
{
	if (bullet.isActive == false) {
        return; // Skip inactive bullets
    }

    // TODO: Calculate the displacement for this frame.
    // Displacement = CurrentVelocity * time.deltaTime.
    // (Note: Since bullets have a stored velocity vector, we don't need trig here,
    // just simple vector scaling).
	Vector2D displacement = { bullet.velocity.x * time.deltaTime, bullet.velocity.y * time.deltaTime };

    // TODO: Command mutator.applyDisplacement() to advance the projectile.
	mutator.applyDisplacement(displacement);
}