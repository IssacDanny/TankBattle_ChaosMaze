#pragma once
#include <vector>
#include "Ledgers/Vector2D.hpp"
#include "Ledgers/AABB.hpp"

// --- The Combatants ---

struct TankData {
    Vector2D position;
    float bodyAngle;      // In radians
    float turretAngle;    // In radians (for the bonus requirement)
    float speed;          // Current movement speed
    
    int health;
    int score;
    int bulletCooldown;   // Frames or time remaining until next shot
    
    AABB boundingBox;     // The physical collider
};

struct BulletData {
    Vector2D position;
    Vector2D velocity;
    
    bool isActive;        // If false, this bullet is "dead" and waiting in the pool
    int ownerID;          // 1 for Player 1, 2 for Player 2 (to prevent self-damage)
    
    AABB boundingBox;
};

// --- The Arena ---

struct LevelData {
    // A collection of static, indestructible walls
    std::vector<AABB> walls;
    
    // We could add spawn points here later if needed
    Vector2D p1Spawn;
    Vector2D p2Spawn;
};