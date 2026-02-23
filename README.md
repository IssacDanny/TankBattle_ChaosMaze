# Tank Battle: Chaos Maze

**Assignment 2: Game Programming (SEM252)**  
**Submission Date:** 02/03/2026  
**Author:** Dinh Gia Kiet - 2252399
**Contributor:**

## Overview
"Tank Battle: Chaos Maze" is a top-down, local multiplayer combat simulation developed in C++ using the SDL2 framework. The programme challenges two players to navigate a treacherous maze, utilizing vector-based movement and Newtonian reflection physics to outmanoeuvre and destroy their opponent.
This project was engineered with a adherence to the my paradigm which I called **Orchestrator-Transformer-Mutator** , ensuring a total separation of mathematical logic, state management, and hardware interfacing.

## Architectural Deep-Dive
While this document provides the essential operational facts, the true soul of the machine resides in our design documentation. 

The validator is strongly encouraged to peruse the **[DESIGN.md](./DESIGN.md)** file for a comprehensive examination of:
*   **The Holistic Architecture:** A detailed breakdown of the Orchestrator-Transformer-Mutator paradigm.
*   **The Chain of Command:** A visual and textual map of the hierarchical delegation that governs the simulation.
*   **Algorithm:** Step-by-step descriptions of the sub-orchestrators, from ballistics reflection to the "Painter's Algorithm" in the rendering engine.

I believe that a programme is only as strong as its design, and the `DESIGN.md` serves as the definitive blueprint for this implementation.

---
## Controls (Local Multiplayer)
The simulation processes simultaneous inputs for two combatants via a single keyboard.

**Player 1 (Left Spawn):**
*   **W / S:** Move Forward / Backward
*   **A / D:** Rotate Tank Body (Left / Right)
*   **Space / F:** Fire Main Gun

**Player 2 (Right Spawn):**
*   **Up / Down Arrows:** Move Forward / Backward
*   **Left / Right Arrows:** Rotate Tank Body (Left / Right)
*   **Enter / M:** Fire Main Gun

---
## Technical Requirements & Build Instructions

### Prerequisites
*   **C++17** compatible compiler (MSVC 2022 recommended).
*   **CMake** (Version 3.10 or higher).
*   **SDL2, SDL2_image, SDL2_ttf** (Included in the `vendor/` directory).

### Build & Run Procedure
The project utilizes a streamlined CMake configuration. All commands should be issued from the root directory:

1.  **Configure the Workshop:**
    ```powershell
    cmake -B build -S .
    ```
2.  **Construct the Programme:**
    ```powershell
    cmake --build build
    ```
3.  **Commence the Simulation:**
    ```powershell
    cmake --build build --target run
    ```

---
## Physics Implementation & Reflection Mathematics
The physics engine was built entirely from scratch, utilising pure vector mathematics and a strict separation of state (Mutators) and pure mathematical calculation (Transformers).

### 1. Vector-Based Movement
Tank and projectile kinematics are calculated using standard trigonometry. The `KinematicsTransformer` calculates the displacement vector per frame using the formula:
*   `velocity.x = speed * cos(θ) * deltaTime`
*   `velocity.y = speed * sin(θ) * deltaTime`

### 2. Collision Detection (AABB)
All spatial entities (Tanks, Bullets, Walls) are encapsulated within Axis-Aligned Bounding Boxes (AABB). The `CollisionTransformer` evaluates intersections by checking for overlaps across both the X and Y axes. 

### 3. Bouncing Physics (Reflection)
When a bullet's AABB intersects with an indestructible wall's AABB, the reflection is handled in two distinct, stateless mathematical steps:

**Step A: Determining the Surface Normal**
The `CollisionTransformer` calculates the shallowest axis of penetration between the projectile and the wall to determine which face was struck. This returns a unit vector representing the surface normal ($\vec{n}$), such as `(0, 1)` for a bottom-face impact or `(-1, 0)` for a left-face impact.

**Step B: The Reflection Formula**
The bullet's current velocity ($\vec{V}_{old}$) and the calculated surface normal ($\vec{n}$) are passed to the `ReflectionTransformer`. This pure function applies the Newtonian reflection formula:
> $\vec{V}_{new} = \vec{V}_{old} - 2(\vec{V}_{old} \cdot \vec{n})\vec{n}$

By calculating the dot product of the old velocity and the normal, scaling it by 2, and subtracting it from the original trajectory, the bullet achieves a mathematically perfect bounce, preserving its momentum on the parallel axis whilst inverting it on the perpendicular axis.

---

## Architectural Note
The codebase is structured using a bespoke "Orchestrator-Transformer-Mutator" pattern. 
*   **Transformers** are pure, stateless functions handling all trigonometry and vector math.
*   **Mutators** are the only authorised agents permitted to alter game state.
*   **Orchestrators** dictate the sequence of the game loop without performing calculations themselves. 
This ensures absolute predictability, eliminates race conditions, and strictly satisfies the Open/Closed Principle.

---

## Asset Sources
*(Note to Validator: All visual and audio assets utilised in this programme were procured from the following sources, adhering to their respective licensing agreements.)*

*   **Tank & Turret Sprites:** [Insert Source/URL Here - e.g., Kenney.nl]
*   **Maze Textures (Walls/Floor):** [Insert Source/URL Here]
*   **Audio (Shooting/Bouncing/Explosions):** [Insert Source/URL Here]
*   **Typography/Fonts:** [Insert Source/URL Here]


***

