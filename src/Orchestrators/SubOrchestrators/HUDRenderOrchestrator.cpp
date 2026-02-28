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
    const std::string p1Text =
        "P1 Health: " + std::to_string(world.player1.health) +
        " | Score: " + std::to_string(world.player1.score);

    const std::string p2Text =
        "P2 Health: " + std::to_string(world.player2.health) +
        " | Score: " + std::to_string(world.player2.score);

    // Top-left
    canvas.drawText(p1Text, 10, 10);

    // Top-right (window is 800 wide in GameLoopOrchestrator)
    constexpr int screenW = 800;
    constexpr int margin = 10;

    // crude but effective: ~8px per character
    constexpr int approxCharW = 8;
    int x2 = screenW - margin - static_cast<int>(p2Text.size()) * approxCharW;
    x2 = std::max(margin, x2);

    canvas.drawText(p2Text, x2, 10);
}