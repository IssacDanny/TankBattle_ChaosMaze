#include "Orchestrators/SubOrchestrators/HUDRenderOrchestrator.hpp"
#include <string>

/**
 * @brief Renders the Health and Score overlay.
 * @param world The current state of the players (const).
 * @param canvas The agent authorised to paint text.
 */
void HUDRenderOrchestrator::execute(
    const WorldLedger& world, 
    CanvasMutator& canvas) 
{
    // TODO: Format the status strings for both players.
    // Example: "P1 Health: 100 | Score: 5"
    
    // TODO: Command canvas.drawText() to display Player 1's info in the top-left.
    // TODO: Command canvas.drawText() to display Player 2's info in the top-right.
}