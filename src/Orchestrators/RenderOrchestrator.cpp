#include "Orchestrators/RenderOrchestrator.hpp"
#include "Mutators/CanvasMutator.hpp"

void RenderOrchestrator::execute(const WorldLedger& world, DisplayLedger& display) {
    
    // 1. Commission the Painter for this frame
    // We wrap the hardware handles in a Mutator agent authorised to paint.
    CanvasMutator canvas(display);

    // 2. Prepare the Canvas
    // We must wipe away the remnants of the previous frame to begin anew.
    canvas.clear();

    // --- The Visual Graphic ---

    // Phase A: The Environment
    // We paint the static maze walls first. They form the backdrop of our theatre.
    mapRenderer.execute(world.maze, canvas, display.wallTexture, display.grassTexture);

    // Phase B: The Actors
    // We paint the tanks and bullets. This specialist will use the 
    // VisualTransformTransformer to handle rotations and unit conversions.
    entityRenderer.execute(world, visualMath, canvas, display);

    // Phase C: The Information Layer
    // Finally, we overlay the HUD. It must be drawn last to ensure it 
    // remains visible even if a tank passes beneath it.
    hudRenderer.execute(world, canvas);

    // 3. Exhibit the Masterpiece
    // We command the canvas to present the finished work to the monitor.
    canvas.present();
}