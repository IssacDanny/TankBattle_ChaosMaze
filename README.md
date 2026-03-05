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
For the physics implementation of the game we conceptualize it as a **State Machine**. The system exists as a sequence of discrete snapshots. The state at time `(t + dt)` is a strictly logical consequence of the state at time `(t)` and the external player inputs `(I)`.

### 2. THE STATE SPACE (S)
The state `S` is defined as the tuple `(T, B, E)`, representing the total knowledge of the universe at any given moment.

#### 2.1 THE TANK STATE (T)
For each combatant `i` in `{1, 2}`:
*   **`P`** (`Vector2D`) : Spatial position `{x, y}`.
*   **`s`** (`float`) : Current scalar speed.
*   **`theta`** (`rad`) : Orientation angle `[0, 2pi)`.
*   **`H`** (`int`) : Health points `[0, 100]`.
*   **`C`** (`float`) : Weapon cooldown timer.
*   **`AABB`** : Physical volume `{Top-left x, Top-left y, width, height}`.

#### 2.2 THE PROJECTILE STATE (B)
For each projectile `j` in the pre-allocated pool `B`:
*   **`P`** (`Vector2D`) : Spatial position `{x, y}`.
*   **`V`** (`Vector2D`) : Velocity vector `{vx, vy}`.
*   **`ID`** (`int`) : Owner identification `{1, 2}`.
*   **`Active`** (`bool`) : Existential status `{True, False}`.
*   **`L`** (`float`) : Remaining lifespan (seconds).
*   **`AABB`** : Physical volume.

#### 2.3 THE ENVIRONMENTAL STATE (E)
The immutable stage:
*   **`W`** (`List`) : A set of static `AABB` structures (Walls).
*   **`Spawn`** (`List`) : Constant starting coordinates for `T1` and `T2`.

### 3. THE INITIAL STATE (Init)
At `t = 0`, the system is initialised as follows:
*   **Tanks:** Placed at `Spawn_1` and `Spawn_2`; `H` (Health points) = 100, `C` (Weapon cooldown timer) = 0.
*   **Projectiles:** All `Active` flags = `False`.
*   **Environment:** Maze walls (`W`) loaded from the level blueprint.

### 4. THE NEXT-STATE OPERATIONS
The mathematical transition of entities relies upon three primary operations:

#### 4.1 OPERATION: LOCOMOTION (Kinematic Integration)
Advances the spatial state of all active entities.

**For Tanks:** `P' = P + [ s * cos(theta), s * sin(theta) ] * dt`
*   `P'` : The resulting position in the next state.
*   `P` : The current position in the 2D plane.
*   `s` : The current scalar speed of the tank.
*   `theta` : The current orientation angle of the chassis (radians).
*   `dt` : Delta Time (the temporal step size).

**For Projectiles:** `P' = P +[ V ] * dt`
*   `P'` : The resulting position in the next state.
*   `P` : The current position.
*   `V` : The current velocity vector `{vx, vy}`.
*   `dt` : Delta Time.

#### 4.2 OPERATION: BALLISTIC LIFE-CYCLES
Governs the entry and exit of projectiles.

**Decay:** `L' = L - dt`
*   `L'` : The remaining lifespan in the next state.
*   `L` : The current lifespan (seconds).
*   `dt` : Delta Time.
*   *Note:* If `L' <= 0`, the projectile's `Active` flag transitions to `False`.

**Spawn:** `V' =[ Bullet_Speed * cos(theta), Bullet_Speed * sin(theta) ]`
*   `V'` : The initial velocity vector assigned to the new projectile.
*   `theta` : The current orientation of the tank's turret (radians).
*   *Note:* Triggered only if `(Shoot_Input == True)` AND `(Cooldown == 0)`.

#### 4.3 OPERATION: CONFLICT RESOLUTION (The Corrective Filter)
Adjudicates state when an intersection `I(AABB_1, AABB_2)` is detected.

**Blocking (Tank vs Wall):** `P' = P_theoretical + MTV`
*   `P'` : The final, corrected position.
*   `P_theoretical` : The position calculated during Locomotion (4.1).
*   `MTV` : Minimum Translation Vector (the shortest path to resolve the overlap and restore legality).

**Reflection (Projectile vs Wall):** `V' = V_old - 2 * (V_old . n) * n`
*   `V'` : The reflected velocity vector for the next state.
*   `V_old` : The incident velocity vector before impact.
*   `n` : The unit surface normal of the impacted wall face.
*   `(.)` : The scalar dot product operator.

**Damage (Projectile vs Tank):** `H' = H - d`
*   `H'` : The health points in the next state.
*   `H` : The current health points.
*   `d` : The discrete damage constant.
*   *Note:* The projectile's `Active` flag simultaneously transitions to `False`.

### 5. THE NEXT-STATE RELATIONSHIP (S -> S')
The transition from State `S` to State `S'` is a composite function. It is defined as a sequence of intermediate "Theoretical States" that are processed and filtered until a valid Final State is achieved.

The logical relationship is defined as:
`S -> [Input] -> [Ballistics] -> [Locomotion] -> [Resolution] -> S'`

#### STEP 1: INPUT INGESTION (S -> S_intent)
The system reads external stimuli (`I`) to update the Intent State.
*   **Logic:** `S_intent = UpdateInput(S, I)`
*   **Formula:** `Input' = PollHardware(I)`
    *   `Input'` : The updated record of player intent (WASD, Arrows, etc.).
    *   `I` : The raw hardware signals from the keyboard.
*   **Result:** The 'buttons' are pressed, but no physical change has occurred.

#### STEP 2: BALLISTIC LIFE-CYCLE (S_intent -> S_life)
The system adjudicates the existence of projectiles within the state space.

**2.1 DECAY:** For all active projectiles: `L' = L - dt`
*   `L'` : The remaining lifespan in the next state.
*   `L` : The current lifespan (seconds).
*   `dt` : Delta Time (the temporal step size).
*   *Note:* If `L' <= 0`, then `Active' = False` (The projectile expires).

**2.2 SPAWN:** If `(Shoot_Input == True)` AND `(Cooldown == 0)`:
*   `Active' = True`, `P' = P_muzzle`, `V' = V_initial`
*   `V'` : `[ Bullet_Speed * cos(theta), Bullet_Speed * sin(theta) ]`
*   `theta` : The current orientation of the tank's turret (radians).
*   *Note:* `Cooldown'` is set to `Max_Cooldown` upon spawning.

*   **Result:** The census of active entities is finalised for the current frame.

#### STEP 3: THEORETICAL LOCOMOTION (S_life -> S_theoretical)
The system applies the Law of Kinematic Integration to all entities confirmed as "Live" in the previous step.

**Formula:** `P_theor = P + V(Input) * dt`
*   `P_theor` : The theoretical position before collision checks.
*   `P` : The current position.
*   `V(Input)`: The velocity vector derived from speed, angle, and input.
*   `dt` : Delta Time.

*   **Result:** Entities move to their new "intended" coordinates. 
    *Note: In this state, entities may mathematically overlap with walls.*

#### STEP 4: CONFLICT RESOLUTION (S_theoretical -> S')
The system applies the Law of Conflict Resolution to the Theoretical State to enforce the physical boundaries of the maze.

**4.1 BLOCKING (Tank vs Wall):** If `Overlap(P_theor, Walls)`: `P' = P_theor + MTV`
*   `P'` : The final, corrected position for the next state.
*   `MTV` : Minimum Translation Vector (the shortest path to resolve overlap and restore physical legality).

**4.2 REFLECTION (Projectile vs Wall):** If `Overlap(P_theor, Walls)`: 
*   **Formula:** `V' = V_old - 2(V_old . n)n`
*   `V'` : The reflected velocity vector.
*   `V_old` : The incident velocity before impact.
*   `n` : The unit surface normal of the impacted wall face.
*   `(.)` : The scalar dot product operator.

**4.3 COMBAT ADJUDICATION:** If `Overlap(P_theor, Enemy_Tank)`: `H' = H - d`
*   `H'` : The health points in the next state.
*   `H` : The current health points.
*   `d` : The discrete damage constant.
*   *Note:* `Active'` of the projectile is simultaneously set to `False`.

*   **Result:** The resulting State `S'` is the only state exhibited to the player.

### 6. THE SOVEREIGN GAME LOOP
The loop is a relentless, sequential cycle. Each iteration represents a single transition from State `S` to State `S'`.

```text
      [ START OF CYCLE ]
             |
             v
    +-----------------------+
    |   I. CHRONOMETER      | <--- Calculate Delta Time (dt)
    +-----------------------+      "How long was the previous silence?"
             |
             v
    +-----------------------+
    |   II. DISPATCH        | <--- Poll Hardware (Input)
    +-----------------------+      "What is the players' intent?"
             |
             v
    +-----------------------+
    |   III. CENSUS         | <--- Ballistic Life-Cycles (Spawn/Decay)
    +-----------------------+      "Who is currently live in the arena?"
             |
             v
    +-----------------------+
    |   IV. ADVANCE         | <--- Theoretical Locomotion (P + V * dt)
    +-----------------------+      "Where do they wish to go?"
             |                     (Note: This state may be physically illegal)
             v
    +-----------------------+
    |   V. UMPIRE           | <--- Conflict Resolution (MTV / Reflect)
    +-----------------------+      "Enforce the laws of the maze."
             |                     (Corrects overlaps before the player sees)
             v
    +-----------------------+
    |   VI. EXHIBITION      | <--- Render View
    +-----------------------+      "Paint the perfected state to the screen."
             |
             +--------------------------- [ REPEAT AD INFINITUM ]
```

### 7. THE ROLE OF DELTA TIME (dt)
Real-world time is continuous, but our simulation is discrete. Delta Time acts as the mathematical bridge between these two realms.

```text
Real-World Time (Continuous) ------------------------------------------------->

Game States (Discrete)       [ S_n ]           [ S_n+1 ]           [ S_n+2 ]
                                |                 |                   |
                                | <--- dt_1 ----> | <--- dt_2 ---->   |
                                |                 |                   |
                                v                 v                   v
                          (Frame 1)         (Frame 2)           (Frame 3)
```

*   **If the computer is FAST:** `dt` is SMALL (e.g., 0.008s). The loop runs often.
*   **If the computer is SLOW:** `dt` is LARGE (e.g., 0.033s). The loop runs rarely.

By multiplying all movement by `dt` (e.g., `Velocity * dt`), we ensure that the Tank travels the **SAME** physical distance in 1 second of real-world time, regardless of how many frames the computer manages to produce.

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

