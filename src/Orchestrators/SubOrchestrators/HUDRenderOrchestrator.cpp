#include "Orchestrators/SubOrchestrators/HUDRenderOrchestrator.hpp"
#include <string>

/**
 * @brief Renders the Health and Score overlay.
 * @param world The current state of the players (const).
 * @param canvas The agent authorised to paint text.
 */
void HUDRenderOrchestrator::execute(const WorldLedger& world, CanvasMutator& canvas) 
{
    // 1. Format the status strings
    std::string p1Text = "P1 Health: " + std::to_string(world.player1.health);
                             
    std::string p2Text = "P2 Health: " + std::to_string(world.player2.health);

    // 2. Command the canvas to paint the text
    // We use Y=25 to give a bit of "breathing room" from the top edge.
    canvas.drawText(p1Text, 20, 25); 

    // We move P2 to X=500. With an 18pt font, this should comfortably 
    // fit the entire string before hitting the 800px right edge.
    canvas.drawText(p2Text, 600, 25); 
}