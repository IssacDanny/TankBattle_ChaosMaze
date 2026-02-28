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
    const Vector2D zeroCentre{ 0.0f, 0.0f };

    // Each wall is an AABB in level.walls
    for (const auto& wall : level.walls)
    {
        canvas.drawSprite(wallTexture, wall, 0.0f, zeroCentre);
    }
}