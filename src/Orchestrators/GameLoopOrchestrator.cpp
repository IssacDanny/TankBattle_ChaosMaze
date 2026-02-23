#include "Orchestrators/GameLoopOrchestrator.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

bool GameLoopOrchestrator::initialise() {
    // 1. Initialise the SDL Frameworks
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;
    if (TTF_Init() == -1) return false;

    // 2. Create the Window (The Theatre)
    display.windowHandle = SDL_CreateWindow(
        "Tank Battle: Chaos Maze",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!display.windowHandle) return false;

    // 3. Create the Renderer (The Painter)
    display.renderContext = SDL_CreateRenderer(
        (SDL_Window*)display.windowHandle, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!display.renderContext) return false;

    // 4. Initialise the Ledgers
    input.isRunning = true;
    time.lastFrameTime = SDL_GetTicks();
    time.deltaTime = 0.0f;

    // 5. Setup Initial World State (A brief sketch for now)
    world.player1.position = { 100.0f, 100.0f };
    world.player1.health = 100;
    world.player1.boundingBox = { 100.0f, 100.0f, 32.0f, 32.0f };

    world.player2.position = { 700.0f, 500.0f };
    world.player2.health = 100;
    world.player2.boundingBox = { 700.0f, 500.0f, 32.0f, 32.0f };

    std::cout << "Game: Hardware and Ledgers initialised." << std::endl;
    return true;
}

void GameLoopOrchestrator::execute() {
    if (!initialise()) {
        std::cerr << "Game: Failed to initialise hardware. Aborting mission." << std::endl;
        return;
    }

    // The Game Loop
    while (input.isRunning) {
        // 1. Synchronise the Watch
        timeOfficer.execute(time);

        // 2. Gather Intelligence
        inputOfficer.execute(input);

        // 3. Advance the Simulation
        worldOfficer.execute(time, input, world);

        // 4. Exhibit the Results
        renderOfficer.execute(world, display);
    }

    shutdown();
}

void GameLoopOrchestrator::shutdown() {
    // Clean up the hardware resources
    SDL_DestroyRenderer((SDL_Renderer*)display.renderContext);
    SDL_DestroyWindow((SDL_Window*)display.windowHandle);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    std::cout << "Game: Hardware released. Mission concluded." << std::endl;
}