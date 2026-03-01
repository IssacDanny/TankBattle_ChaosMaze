#include "Orchestrators/SubOrchestrators/MapRenderOrchestrator.hpp"
#include <SDL.h>
/**
 * @brief Renders the static maze walls.
 * @param level The data containing wall positions (const).
 * @param canvas The agent authorised to paint the screen.
 * @param wallTexture The visual asset for the walls.
 */


void MapRenderOrchestrator::execute(const LevelData& level, CanvasMutator& canvas, void* wallTexture, void* grassTexture) 
{
    Vector2D dummyCentre = {0.0f, 0.0f};

    // 1. Lay the Terrain (Seamless Tiling)
    // We query the grass texture to ensure we tile it without gaps
    int grassW = 50, grassH = 50; // Default fallback
    if (grassTexture) {
        SDL_QueryTexture(static_cast<SDL_Texture*>(grassTexture), NULL, NULL, &grassW, &grassH);
    }

    // We tile across the 800x600 theatre of war
    for (int y = 0; y < 600; y += grassH) {
        for (int x = 0; x < 800; x += grassW) {
            // We create a temporary AABB for the grass tile
            AABB grassBox = { static_cast<float>(x), static_cast<float>(y), 
                             static_cast<float>(grassW), static_cast<float>(grassH) };
            
            // The CanvasMutator will draw this at its native size
            canvas.drawSprite(grassTexture, grassBox, 0.0f, dummyCentre);
        }
    }

    // 2. Build the Walls (Proportional & Centred)
    // Because our CanvasMutator::drawSprite is now "Sophisticated," 
    // it will automatically query the wallTexture's native size and 
    // centre it over the physical 50x50 wall AABB.
    for (const AABB& wall : level.walls) {
        canvas.drawSprite(wallTexture, wall, 0.0f, dummyCentre);
    }
}