# CONTRIBUTION.md: Standing Orders for the Regiment

Welcome to the **Tank Battle: Chaos Maze** endeavour.

## I. The Architectural Doctrine
Our system follows is designed follow my paradigm, I called it, the **Orchestrator-Transformer-Mutator** . Adherence to these roles is non-negotiable:

1.  **Ledgers (S):** Passive data structures. They hold state but possess no logic.
2.  **Transformers:** Pure, stateless objects. They take data, perform calculations, and return results. They **never** mutate state.
3.  **Mutators:** Authorised agents of change. They are the only specialists permitted to alter a Ledger or command the hardware (SDL2).
4.  **Orchestrators (A):** The commanders. They coordinate the flow of data between Transformers and Mutators.

## II. The Contracts (Headers)
The `.hpp` files in the `include/` directory are the **Contracts** authored by the Me. 
*   **Do not alter the headers.** If you believe a contract requires amendment, you must petition me directly.
*   Implement your logic strictly within the corresponding `.cpp` files in the `src/` directory.

## III. Task Distribution (Order of Battle)

### **Developer A: Implement The Ballistic**
*   **Focus:** Physics logic and conflict resolution.
*   **Assigned Files:**
    *   `src/Transformers/CollisionTransformer.cpp`
    *   `src/Transformers/ReflectionTransformer.cpp`
    *   `src/Orchestrators/SubOrchestrators/CollisionResolutionOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/TankWallCollisionOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/BulletWallCollisionOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/BulletTankCollisionOrchestrator.cpp`

### **Developer B: Implement The Motion**
*   **Focus:** Entity lifecycles and locomotion.
*   **Assigned Files:**
    *   `src/Mutators/TankMutator.cpp`
    *   `src/Mutators/BulletMutator.cpp`
    *   `src/Transformers/KinematicsTransformer.cpp`
    *   `src/Orchestrators/SubOrchestrators/TankMovementOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/BulletMovementOrchestrator.cpp`
    *   `src/Orchestrators/WorldUpdateOrchestrator.cpp`

### **Developer C: Implement the Input Output**
*   **Focus:** Hardware interface, rendering, and system timing.
*   **Assigned Files:**
    *   `src/Mutators/CanvasMutator.cpp`
    *   `src/Transformers/VisualTransformTransformer.cpp`
    *   `src/Orchestrators/SubOrchestrators/MapRenderOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/EntityRenderOrchestrator.cpp`
    *   `src/Orchestrators/SubOrchestrators/HUDRenderOrchestrator.cpp`
    *   `src/Orchestrators/RenderOrchestrator.cpp`
    *   `src/Orchestrators/TimeOrchestrator.cpp`
    *   `src/Orchestrators/InputOrchestrator.cpp`

## IV. Coding Convention.
*   **Naming:** Use `PascalCase` for Classes and `camelCase` for methods and variables.
*   **The Entry Point:** All Orchestrators use a single public method named `execute()`.
*   **Purity:** Transformers must remain `const`. Do not attempt to sneak state into them.
*   **Comments:** Follow the `TODO` guides provided in the skeletal implementations.

## V. The Workshop (Build Instructions)
All commands must be issued from the project root.

1.  **Configure:** `cmake -B build -S .`
2.  **Build:** `cmake --build build`
3.  **Run:** `cmake --build build --target run`
4.  **Clear the build:** `cmake -E remove_directory build`