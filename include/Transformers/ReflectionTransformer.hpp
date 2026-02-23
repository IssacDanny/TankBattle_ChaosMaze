#pragma once
#include "Ledgers/Vector2D.hpp"

class ReflectionTransformer {
public:
    // Implements: V_new = V_old - 2(V_old . n)n
    Vector2D calculateReflection(const Vector2D& incidentVelocity, const Vector2D& surfaceNormal) const;
};