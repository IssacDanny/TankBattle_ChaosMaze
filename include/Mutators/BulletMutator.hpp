#pragma once
#include "Ledgers/EntityData.hpp"

class BulletMutator {
private:
    BulletData& target;

public:
    BulletMutator(BulletData& bullet);

    // --- State Alteration Methods ---

    void applyDisplacement(const Vector2D& delta);
    void setVelocity(const Vector2D& newVelocity);
    
    // Used when a bullet strikes a tank or exceeds its lifespan
    void deactivate();
    
    // Used to fire a new bullet from the pool
    void spawn(const Vector2D& pos, const Vector2D& vel, int owner);
};