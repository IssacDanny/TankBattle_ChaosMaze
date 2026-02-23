#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Transformers/VisualTransformTransformer.hpp"
#include "Mutators/CanvasMutator.hpp"

class EntityRenderOrchestrator {
public:
    /**
     * @brief Renders the dynamic actors: Tanks and Bullets.
     * @param world The current state of all entities (const)
     * @param math The specialist for radian-to-degree and centre-point calculations (const)
     * @param canvas The agent authorised to paint the screen
     * @param display The ledger containing the necessary textures (const)
     */
    void execute(const WorldLedger& world, 
              const VisualTransformTransformer& math, 
              CanvasMutator& canvas, 
              const DisplayLedger& display);
};