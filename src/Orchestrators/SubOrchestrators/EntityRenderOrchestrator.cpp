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
    auto renderTank = [&](const TankData& tank)
        {
            const Vector2D pivot = math.calculateCentre(tank.boundingBox);
            const float bodyDeg = math.radiansToDegrees(tank.bodyAngle);
            const float turretDeg = math.radiansToDegrees(tank.turretAngle);

            canvas.drawSprite(display.tankBodyTexture, tank.boundingBox, bodyDeg, pivot);
            canvas.drawSprite(display.tankTurretTexture, tank.boundingBox, turretDeg, pivot);
        };

    // Player 1 + Player 2
    renderTank(world.player1);
    renderTank(world.player2);

    // Bullets (object pool)
    for (const auto& bullet : world.bulletPool)
    {
        if (!bullet.isActive) continue;

        const Vector2D pivot = math.calculateCentre(bullet.boundingBox);
        canvas.drawSprite(display.bulletTexture, bullet.boundingBox, 0.0f, pivot);
    }
}