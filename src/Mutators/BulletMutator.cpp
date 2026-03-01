#include "Mutators/BulletMutator.hpp"

/**
 * @brief Binds the mutator to a specific bullet in the pool.
 */
BulletMutator::BulletMutator(BulletData& bullet) : target(bullet) {}

void BulletMutator::applyDisplacement(const Vector2D& delta) 
{
    // TODO: Update target.position and target.boundingBox.
    target.position.x += delta.x;
    target.position.y += delta.y;

    target.boundingBox.x = target.position.x;
    target.boundingBox.y = target.position.y;
}

void BulletMutator::setVelocity(const Vector2D& newVelocity) 
{
    // TODO: Set target.velocity to the new reflected or initial vector.
    target.velocity = newVelocity;
}

void BulletMutator::deactivate() 
{
    // TODO: Set target.isActive to false.
    // This returns the bullet to the "available" pool.
    target.isActive = false;
}

void BulletMutator::spawn(const Vector2D& pos, const Vector2D& vel, int owner) 
{
    // TODO: Set target.isActive to true.
    target.isActive = true;

    // TODO: Initialise position, velocity, ownerID, and boundingBox.
    target.position = pos;
    target.boundingBox.x = pos.x;
    target.boundingBox.y = pos.y;
    target.velocity = vel;
    target.ownerID = owner;
}