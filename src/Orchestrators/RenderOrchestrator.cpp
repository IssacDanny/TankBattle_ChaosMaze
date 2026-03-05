#include "Orchestrators/RenderOrchestrator.hpp"
#include "Mutators/CanvasMutator.hpp"

void RenderOrchestrator::execute(const WorldLedger& world, DisplayLedger& display) {
    CanvasMutator canvas(display);
    canvas.clear();

    if (world.state == GameState::START_SCREEN) {
        canvas.drawText("TANK BATTLE: CHAOS MAZE", 250, 250);
        canvas.drawText("PRESS ENTER OR SPACE TO START", 220, 300);
    } 
    else if (world.state == GameState::PLAYING) {
        mapRenderer.execute(world.maze, canvas, display.wallTexture, display.grassTexture);
        entityRenderer.execute(world, visualMath, canvas, display);
        hudRenderer.execute(world, canvas);
    } 
    else if (world.state == GameState::GAME_OVER) {
        std::string winMsg = "PLAYER " + std::to_string(world.winnerID) + " IS VICTORIOUS!";
        canvas.drawText(winMsg, 250, 250);
        canvas.drawText("PRESS R TO RESTART", 280, 300);
    }

    canvas.present();
}