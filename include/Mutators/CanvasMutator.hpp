#pragma once
#include <string>
#include "Ledgers/GameLedgers.hpp"

class CanvasMutator {
private:
    DisplayLedger& display;

public:
    CanvasMutator(DisplayLedger& ledger);

    // --- Hardware Alteration Methods ---

    void clear();   // Wipes the canvas for a new frame
    void present(); // Exhibits the finished frame to the monitor

    // The primary drawing command, supporting rotation around a centre point
    void drawSprite(void* texture, const AABB& destination, float angleDegrees, const Vector2D& centre);
    
    // For the HUD requirements
    void drawText(const std::string& text, int x, int y);
};