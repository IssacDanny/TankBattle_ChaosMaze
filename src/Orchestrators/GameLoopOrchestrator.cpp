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

    SDL_Renderer* ren = (SDL_Renderer*)display.renderContext;

    // Load the Sprites
    display.p1Body   = IMG_LoadTexture(ren, "assets/sprites/tankBody_blue.png");
    display.p1Turret = IMG_LoadTexture(ren, "assets/sprites/tankBlue_barrel.png");
    
    display.p2Body   = IMG_LoadTexture(ren, "assets/sprites/tankBody_red.png");
    display.p2Turret = IMG_LoadTexture(ren, "assets/sprites/tankRed_barrel.png");
    
    display.wallTexture     = IMG_LoadTexture(ren, "assets/sprites/wall.png");
    display.grassTexture    = IMG_LoadTexture(ren, "assets/sprites/grass.png");
    display.p1BulletTexture = IMG_LoadTexture(ren, "assets/sprites/bullet_blue.png");
    display.p2BulletTexture = IMG_LoadTexture(ren, "assets/sprites/bullet_red.png");

    // Load the Font (Size 24)
    display.fontAsset = TTF_OpenFont("assets/fonts/combat_font.ttf", 24);

    if (!display.p1Body || !display.p2Body || !display.fontAsset) {
        std::cerr << "Report: Failed to load assets! Check your file paths." << std::endl;
        return false;
    }

    // 4. Initialise the Ledgers
    input.isRunning = true;
    time.lastFrameTime = SDL_GetTicks();
    time.deltaTime = 0.0f;

    resetWorld(); 
    world.state = GameState::START_SCREEN;

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
        switch (world.state) {
            case GameState::START_SCREEN:
                // If either player presses their 'Shoot' key (Space/Enter), begin the match
                if (input.player1.shoot || input.player2.shoot) {
                    world.state = GameState::PLAYING;

                    input.player1.shoot = false;
                    input.player2.shoot = false;
                }
                break;

            case GameState::PLAYING:
                // Advance the simulation
                worldOfficer.execute(time, input, world);
                break;

            case GameState::GAME_OVER:
                // If a restart is requested (we'll use the 'Shoot' key for simplicity here), 
                // reset the world and return to the start.
                if (input.restartRequested) {
                    resetWorld();
                    world.state = GameState::START_SCREEN;
                    input.restartRequested = false;
                }
                break;
        }

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

void GameLoopOrchestrator::resetWorld() {
    // 1. Clear the Ledgers
    // We must wipe the previous state to avoid duplicating walls or carrying over old munitions.
    world.maze.walls.clear();
    world.bulletPool.clear();
    world.winnerID = 0;

    // 2. Define the Architectural Blueprint (The Maze)
    const std::vector<std::string> LEVEL_MAP = {
        "WWWWWWWWWWWWWWWW",
        "W              W",
        "W  1        2  W",
        "W    WWWWWW    W",
        "W    W    W    W",
        "W              W",
        "W      WW      W",
        "W              W",
        "W    W    W    W",
        "W    WWWWWW    W",
        "W              W",
        "WWWWWWWWWWWWWWWW"
    };

    const float TILE_SIZE = 50.0f;

    // 3. Parse the Map and Commission the Entities
    for (size_t row = 0; row < LEVEL_MAP.size(); ++row) {
        for (size_t col = 0; col < LEVEL_MAP[row].size(); ++col) {
            char tile = LEVEL_MAP[row][col];
            Vector2D pos = { col * TILE_SIZE, row * TILE_SIZE };

            if (tile == 'W') {
                // Add a solid wall to the maze ledger
                world.maze.walls.push_back({ pos.x, pos.y, TILE_SIZE, TILE_SIZE });
            } 
            else if (tile == '1') {
                // Initialise Player 1 (Blue)
                world.player1.position = pos;
                world.player1.boundingBox = { pos.x, pos.y, 32.0f, 32.0f };
                world.player1.health = 100;
                world.player1.score = 0;
                world.player1.bodyAngle = 0.0f;   // Facing East
                world.player1.turretAngle = 0.0f;
                world.player1.bulletCooldown = 0;
            }
            else if (tile == '2') {
                // Initialise Player 2 (Red)
                world.player2.position = pos;
                world.player2.boundingBox = { pos.x, pos.y, 32.0f, 32.0f };
                world.player2.health = 100;
                world.player2.score = 0;
                world.player2.bodyAngle = 3.14159f; // Facing West
                world.player2.turretAngle = 3.14159f;
                world.player2.bulletCooldown = 0;
            }
        }
    }

    // 4. Re-stock the Armoury
    // We pre-allocate 30 clean, inactive bullets to the pool.
    world.bulletPool.assign(30, BulletData{});
    for (auto& bullet : world.bulletPool) {
        bullet.isActive = false;
        bullet.lifespan = 0.0f;
        bullet.boundingBox = { 0.0f, 0.0f, 8.0f, 8.0f };
    }

    std::cout << "Quartermaster: World state has been reset to factory specifications." << std::endl;
}