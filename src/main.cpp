#include "Orchestrators/GameLoopOrchestrator.hpp"

/**
 * The Grand Entry Point.
 * Its only duty is to instantiate the Game and commence the loop.
 */
int main(int argc, char* argv[]) {
    GameLoopOrchestrator game{};
    
    // The Sovereign takes command
    game.execute();
    
    return 0;
}