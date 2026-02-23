#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Mutators/CanvasMutator.hpp"

class HUDRenderOrchestrator {
public:
    /**
     * @brief Renders the Heads-Up Display (Health and Score).
     * @param world The current state of the players (const)
     * @param canvas The agent authorised to paint text on the screen
     */
    void execute(const WorldLedger& world, 
              CanvasMutator& canvas);
};