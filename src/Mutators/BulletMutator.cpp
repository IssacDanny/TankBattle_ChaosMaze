#include "Mutators/BulletMutator.hpp"

/**
 * @brief Binds the mutator to a specific bullet in the pool.
 */
BulletMutator::BulletMutator(BulletData& bullet) : target(bullet) {}

void BulletMutator::applyDisplacement(const Vector2D& delta) 
{
    // TODO: Update target.position and target.boundingBox.
}

void BulletMutator::setVelocity(const Vector2D& newVelocity) 
{
    // TODO: Set target.velocity to the new reflected or initial vector.
}

void BulletMutator::deactivate() 
{
    // TODO: Set target.isActive to false.
    // This returns the bullet to the "available" pool.
}

void BulletMutator::spawn(const Vector2D& pos, const Vector2D& vel, int owner) 
{
    // TODO: Set target.isActive to true.
    // TODO: Initialise position, velocity, ownerID, and boundingBox.
}