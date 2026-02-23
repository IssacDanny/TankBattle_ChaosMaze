#include "Orchestrators/TimeOrchestrator.hpp"
#include <SDL.h>

void TimeOrchestrator::execute(TimeLedger& ledger) {
    // 1. Capture the current system tick count
    unsigned int currentTime = SDL_GetTicks();

    // 2. Calculate the difference since the last frame
    unsigned int frameTime = currentTime - ledger.lastFrameTime;

    // 3. Convert to seconds (Delta Time)
    // We cap the delta time at 0.1s to prevent massive physics "jumps" 
    // if the window is moved or the system stutters.
    ledger.deltaTime = frameTime / 1000.0f;
    if (ledger.deltaTime > 0.1f) {
        ledger.deltaTime = 0.1f;
    }

    // 4. Update the ledger for the next cycle
    ledger.lastFrameTime = currentTime;
}