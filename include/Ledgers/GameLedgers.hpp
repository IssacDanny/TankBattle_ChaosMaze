#pragma once
#include <vector>
#include <map>
#include "Ledgers/EntityData.hpp"

// --- 1. The Chronometer ---
struct TimeLedger {
    float deltaTime;           // Time elapsed since last frame (in seconds)
    unsigned int lastFrameTime; // System tick count at start of frame
};

// --- 2. The Dispatch ---
struct InputLedger {
    bool isRunning;            // Main loop condition
    
    // We define the role of "PlayerInput" so it can be passed to specialists
    struct PlayerInput {
        bool up, down, left, right;
        bool shoot;
        bool rotateTurretLeft, rotateTurretRight; // For bonus
    };

    PlayerInput player1;
    PlayerInput player2;
};

// --- 3. The Simulation State ---
struct WorldLedger {
    TankData player1;
    TankData player2;
    
    // A pre-allocated pool of ammunition to avoid runtime allocation
    std::vector<BulletData> bulletPool;
    
    LevelData maze;
};

// --- 4. The Hardware State ---
// We use void* here to decouple the header from SDL2. 
// The implementation (Mutator) will cast these to SDL_Window* and SDL_Renderer*.
struct DisplayLedger {
    void* windowHandle;
    void* renderContext;
    
    void* p1Body;
    void* p1Turret;
    void* p1BulletTexture;
    void* p2Body;
    void* p2Turret;
    void* p2BulletTexture;
    
    void* wallTexture;
    void* grassTexture;
    void* fontAsset;
};