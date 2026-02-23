#include "Orchestrators/SubOrchestrators/EntityRenderOrchestrator.hpp"

/**
 * @brief Renders the dynamic actors (Tanks and Bullets).
 * @param world The current state of all entities (const).
 * @param math The specialist for unit conversions and centre-points (const).
 * @param canvas The agent authorised to paint the screen.
 * @param display The ledger containing the textures (const).
 */
void EntityRenderOrchestrator::execute(
    const WorldLedger& world, 
    const VisualTransformTransformer& math, 
    CanvasMutator& canvas, 
    const DisplayLedger& display) 
{
    // TODO: Render Player 1 and Player 2 Tanks.
    // For each tank:
    //   1. Use math.calculateCentre(tank.boundingBox) to find the pivot.
    //   2. Use math.radiansToDegrees() for both bodyAngle and turretAngle.
    //   3. Command canvas.drawSprite() for the Body.
    //   4. Command canvas.drawSprite() for the Turret (using the same centre).

    // TODO: Render Active Bullets.
    // Iterate through world.bulletPool:
    //   If bullet.isActive is true:
    //     Command canvas.drawSprite() using the bulletTexture.
}