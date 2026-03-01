#include "Orchestrators/SubOrchestrators/EntityRenderOrchestrator.hpp"
#include <cmath>

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
    const float SPRITE_OFFSET = 90.0f; // Correcting North-facing sprites to East
    Vector2D dummy = {0, 0};

    // --- Render Player 1 ---
    float p1BodyDeg = math.radiansToDegrees(world.player1.bodyAngle) + SPRITE_OFFSET;
    float p1TurretDeg = math.radiansToDegrees(world.player1.turretAngle) + SPRITE_OFFSET;
    canvas.drawSprite(display.p1Body, world.player1.boundingBox, p1BodyDeg, dummy);
    canvas.drawSprite(display.p1Turret, world.player1.boundingBox, p1TurretDeg, dummy);

    // --- Render Player 2 ---
    float p2BodyDeg = math.radiansToDegrees(world.player2.bodyAngle) + SPRITE_OFFSET;
    float p2TurretDeg = math.radiansToDegrees(world.player2.turretAngle) + SPRITE_OFFSET;
    canvas.drawSprite(display.p2Body, world.player2.boundingBox, p2BodyDeg, dummy);
    canvas.drawSprite(display.p2Turret, world.player2.boundingBox, p2TurretDeg, dummy);


    // --- Render the Munitions ---
    for (const auto& bullet : world.bulletPool) {
        if (bullet.isActive) {
            // Calculate the visual angle based on velocity
            float bulletAngleRad = std::atan2(bullet.velocity.y, bullet.velocity.x);
            float bulletAngleDeg = math.radiansToDegrees(bulletAngleRad) + SPRITE_OFFSET;

            // SELECT THE CORRECT TRACER BASED ON THE OWNER
            // If ownerID is 1, use P1's blue texture; otherwise, use P2's red.
            void* tracerTex = (bullet.ownerID == 1) ? display.p1BulletTexture : display.p2BulletTexture;
            
            // Use our "Aspect Fit" drawSprite method
            canvas.drawSprite(tracerTex, bullet.boundingBox, bulletAngleDeg, dummy);
        }
    }
}