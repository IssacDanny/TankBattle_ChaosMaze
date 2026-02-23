#include "Orchestrators/SubOrchestrators/MapRenderOrchestrator.hpp"

/**
 * @brief Renders the static maze walls.
 * @param level The data containing wall positions (const).
 * @param canvas The agent authorised to paint the screen.
 * @param wallTexture The visual asset for the walls.
 */
void MapRenderOrchestrator::execute(
    const LevelData& level, 
    CanvasMutator& canvas, 
    void* wallTexture) 
{
    // TODO: Iterate through every AABB in level.walls.
    // TODO: For each wall, command canvas.drawSprite().
    // Note: Walls are static, so angleDegrees should be 0.0f and 
    // the centre point can be a zeroed Vector2D.
}