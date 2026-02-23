#include "Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.hpp"

/**
 * @brief Prevents tanks from entering wall geometry.
 * @param collisionMath Used to detect overlaps.
 * @param tankMutator The agent to be corrected if a collision occurs.
 * @param level The collection of walls to check against.
 */
void TankWallCollisionOrchestrator::execute(
    const CollisionTransformer& collisionMath, 
    TankMutator& tankMutator, 
    const LevelData& level) 
{
    // TODO: Iterate through every AABB wall in level.walls.
    // TODO: Use collisionMath.isIntersecting() to check the tank's bounding box against the wall.
    // TODO: If an intersection is found, calculate the necessary displacement to push the tank 
    //       back out of the wall and command tankMutator.applyDisplacement().
}