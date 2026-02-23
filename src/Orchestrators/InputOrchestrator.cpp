#include "Orchestrators/InputOrchestrator.hpp"
#include <SDL.h>

void InputOrchestrator::execute(InputLedger& ledger) {
    SDL_Event event;

    // Poll all pending events in the queue (The Batch)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            ledger.isRunning = false;
        }

        // Handle Key Presses
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            bool isPressed = (event.type == SDL_KEYDOWN);
            SDL_Keycode key = event.key.keysym.sym;

            // --- Player 1 Mapping (WASD + Space/F) ---
            switch (key) {
                case SDLK_w: ledger.player1.up = isPressed;    break;
                case SDLK_s: ledger.player1.down = isPressed;  break;
                case SDLK_a: ledger.player1.left = isPressed;  break;
                case SDLK_d: ledger.player1.right = isPressed; break;
                case SDLK_f: 
                case SDLK_SPACE: ledger.player1.shoot = isPressed; break;

                // --- Player 2 Mapping (Arrows + Enter/M) ---
                case SDLK_UP:    ledger.player2.up = isPressed;    break;
                case SDLK_DOWN:  ledger.player2.down = isPressed;  break;
                case SDLK_LEFT:  ledger.player2.left = isPressed;  break;
                case SDLK_RIGHT: ledger.player2.right = isPressed; break;
                case SDLK_m:
                case SDLK_RETURN: ledger.player2.shoot = isPressed; break;
                
                // --- Bonus: Independent Turret Rotation ---
                case SDLK_q: ledger.player1.rotateTurretLeft = isPressed;  break;
                case SDLK_e: ledger.player1.rotateTurretRight = isPressed; break;
                case SDLK_k: ledger.player2.rotateTurretLeft = isPressed;  break;
                case SDLK_l: ledger.player2.rotateTurretRight = isPressed; break;
            }
        }
    }
}