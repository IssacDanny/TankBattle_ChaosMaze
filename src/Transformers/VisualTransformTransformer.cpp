#include "Transformers/VisualTransformTransformer.hpp"

/**
 * @brief Converts radians (physics) to degrees (rendering).
 */
float VisualTransformTransformer::radiansToDegrees(float radians) const 
{
    // TODO: Return radians * (180.0f / PI).
    return 45.0;
}

/**
 * @brief Calculates the centre point of an AABB.
 * @return A Vector2D representing the pivot point for rotation.
 */
Vector2D VisualTransformTransformer::calculateCentre(const AABB& box) const 
{
    // TODO: Return { box.width / 2.0f, box.height / 2.0f }.
    // Note: This is the local centre relative to the sprite's top-left.
    return { 0.0f, 0.0f };
}