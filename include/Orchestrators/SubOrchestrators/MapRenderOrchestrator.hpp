#pragma once
#include "Ledgers/EntityData.hpp"
#include "Mutators/CanvasMutator.hpp"

class MapRenderOrchestrator {
public:
    /**
     * @brief Renders the static maze environment.
     * @param level The map data containing wall positions (const)
     * @param canvas The agent authorised to paint the screen
     * @param wallTexture The visual asset for the walls
     */
    void execute(const LevelData& level, 
              CanvasMutator& canvas, 
              void* wallTexture);
};