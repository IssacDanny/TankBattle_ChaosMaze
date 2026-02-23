#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Transformers/VisualTransformTransformer.hpp"
#include "Orchestrators/SubOrchestrators/MapRenderOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/EntityRenderOrchestrator.hpp"
#include "Orchestrators/SubOrchestrators/HUDRenderOrchestrator.hpp"

class RenderOrchestrator {
private:
    // Shared Transformer
    VisualTransformTransformer visualMath;

    // Subordinate Specialists
    MapRenderOrchestrator    mapRenderer;
    EntityRenderOrchestrator entityRenderer;
    HUDRenderOrchestrator    hudRenderer;

public:
    /**
     * @brief Orchestrates the rendering of the entire scene.
     */
    void execute(const WorldLedger& world, DisplayLedger& display);
};