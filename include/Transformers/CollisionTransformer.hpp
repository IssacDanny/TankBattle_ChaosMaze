#pragma once
#include "Ledgers/AABB.hpp"
#include "Ledgers/Vector2D.hpp"

class CollisionTransformer {
public:
    // The fundamental AABB intersection check
    bool isIntersecting(const AABB& a, const AABB& b) const;

    // Determines the surface normal of the static object (b) relative to the moving object (a)
    // Essential for calculating the bounce direction
    Vector2D calculateSurfaceNormal(const AABB& moving, const AABB& stationary) const;
};