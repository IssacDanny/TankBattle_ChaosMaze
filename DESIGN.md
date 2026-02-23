# Software Design Description: Tank Battle - Chaos Maze

## System Overview: The Holistic Architecture

Before examining the individual components of this programme, one must first understand the governing philosophy of its construction. The programme is built upon the fundamental maxim that **Algorithms + Data Structures = Programs**. The system’s components are categorised into four distinct roles:

1.  **The Ledgers (Data Structures - $S$):** Purely passive, flat containers of state. They possess no logic and no behaviour. They are the "messages" passed through the system.
2.  **The Mathematicians (Transformers):** Pure, stateless functions. They receive data, perform the vector mathematics and collision geometry required by the specification, and return a result. They have no memory and alter no state.
3.  **The State Representatives (Mutators):** The only entities authorised to alter the Ledgers. They encapsulate the state and provide a strictly controlled interface for modification.
4.  **The Chain of Command (Orchestrators - $A$):** The algorithms themselves. They own the Ledgers, instantiate the Transformers and Mutators, and dictate the exact sequence of operations. They do not perform mathematics or alter state directly; they merely delegate.

The entire simulation operates as a continuous, deterministic loop, divided into four primary branches: **Time** (synchronisation), **Input** (gathering human intent), **World Update** (physics and collision resolution), and **Render** (visual exhibition). 

The following master schematic illustrates this strict hierarchy, demonstrating the unidirectional flow of dependencies and the absolute segregation of duties.

<img width="16384" height="7646" alt="image" src="https://github.com/user-attachments/assets/3892d035-8fa7-47ac-a841-d098e4bc7a0c" />


*(The reader is advised to refer back to this schematic whilst navigating the detailed specifications of the Sub-Orchestrators in the subsequent sections.)*


### Section 1: The holistic View

This section details the highest level of abstraction within the "Tank Battle - Chaos Maze" programme. Here, we define the master state containers and the root algorithm that governs the continuous, reactive lifecycle of the Game.

#### 1.1 The Master Ledgers (Data Structures)
In accordance with our strict separation of state and behaviour, the overarching state of the programme is divided into four distinct, passive data structures. These ledgers contain no logic; they are the "messages" passed along our command chain.

*   **`TimeLedger`**: The chronometer of our simulation. It records the absolute time of the previous frame and the calculated `deltaTime` ($\Delta t$) for the current frame. This ensures that all subsequent physics calculations remain entirely independent of the hardware's processing speed.
*   **`InputLedger`**: The record of human intent. It stores the current state of the keyboard (e.g., which keys are currently depressed) and vital system signals, most notably a boolean flag (`isRunning`) indicating whether the user has requested to terminate the programme.
*   **`WorldLedger`**: The grand repository of the simulation. It encapsulates the entire logical and physical state of the game, including the `TankData` for both combatants, the pre-allocated pool of `BulletData`, and the `LevelData` representing the maze.
*   **`DisplayLedger`**: The hardware manifest. It holds the low-level pointers required to interface with the operating system's graphics API (such as the window handle and rendering context), alongside the loaded texture assets required for visual exhibition.

#### 1.2 `GameLoopOrchestrator` (The Root Algorithm)
The `GameLoopOrchestrator` is the Sovereign Class of our architecture. It acts as the supreme commander, owning the four Master Ledgers and the four primary Sub-Orchestrators (`TimeOrchestrator`, `InputOrchestrator`, `WorldUpdateOrchestrator`, and `RenderOrchestrator`). 

Crucially, this class possesses absolutely no knowledge of trigonometry, collision physics, or pixel rendering. Its single responsibility is to enforce the strict, sequential execution of the game loop.

**The High-Level Algorithm (`main` method):**

1.  **Initialisation:** The Orchestrator allocates the Master Ledgers and instantiates its subordinate Orchestrators.
2.  **The Reactive Loop:** The Orchestrator enters a continuous `while` loop, conditioned upon the `isRunning` flag within the `InputLedger`.
3.  **Phase 1: Temporal Update:** The Orchestrator commands the `TimeOrchestrator` to read the system clock and update the `TimeLedger`.
4.  **Phase 2: Input Gathering:** The Orchestrator commands the `InputOrchestrator` to poll the operating system for hardware events and update the `InputLedger`.
5.  **Phase 3: World Simulation:** The Orchestrator commands the `WorldUpdateOrchestrator`. It passes the `TimeLedger` and `InputLedger` as read-only (`const`) references, and grants mutable access to the `WorldLedger`. The subordinate is tasked with advancing the game's state by one $\Delta t$ step.
6.  **Phase 4: Visual Exhibition:** The Orchestrator commands the `RenderOrchestrator`. It passes the newly updated `WorldLedger` as a read-only reference, and grants mutable access to the `DisplayLedger`. The subordinate is tasked with painting the current state to the monitor.
7.  **Iteration:** The loop returns to Step 2 and repeats until a termination signal is received.


### Section 2: The Temporal & Input

This section details the algorithms of the two foundational Sub-Orchestrators. Before any physics can be calculated or any pixels painted, the programme must first consult its chronometer and read the dispatches from the operating system.

#### 2.1 `TimeOrchestrator` (The Chronometer Algorithm)
The `TimeOrchestrator` is a highly specialised clerk. Its sole responsibility is to measure the precise duration that has elapsed since it was last called, ensuring that our physics engine operates smoothly regardless of the hardware's processing speed. It is granted mutable access exclusively to the `TimeLedger`.

**The High-Level Algorithm (`main` method):**

1.  **Consult the System Clock:** The Orchestrator queries the underlying framework (e.g., `SDL_GetTicks()` or `std::chrono`) to ascertain the current absolute time in milliseconds.
2.  **Calculate the Delta:** It subtracts the `lastFrameTime` (stored within the `TimeLedger` from the previous cycle) from the current time. This yields the raw elapsed time.
3.  **Unit Conversion:** It converts this raw elapsed time into a fractional second (e.g., dividing by 1000.0f). This value becomes our $\Delta t$ (`deltaTime`).
4.  **Safety Cap (The Gentleman's Limit):** To prevent the physics engine from calculating catastrophic, wall-phasing velocities in the event of a severe system lag or window drag, the Orchestrator clamps the maximum $\Delta t$ to a sensible upper bound (e.g., 0.05 seconds).
5.  **Record Keeping:** It updates the `TimeLedger`'s `deltaTime` with the calculated value, and overwrites the `lastFrameTime` with the current absolute time, preparing the ledger for the next iteration.

#### 2.2 `InputOrchestrator` (The Dispatch Algorithm)
The `InputOrchestrator` acts as our communications officer. Its duty is to drain the hardware event queue and translate those events into a clean, passive state within the `InputLedger`.

**The High-Level Algorithm (`main` method):**

1.  **Queue Interrogation:** The Orchestrator enters a `while` loop, continuously polling the operating system's event queue until it is entirely empty. It processes these events in a strict First-In, First-Out (FIFO) manner.
2.  **Event Classification:** For each event retrieved, the Orchestrator inspects its type.
3.  **System Directives (Quit):** If the event is a system-level termination request (such as the user clicking the window's 'X' button or pressing Alt+F4), the Orchestrator immediately sets the `isRunning` boolean within the `InputLedger` to `false`. This will gracefully collapse the Sovereign loop on the next cycle.
4.  **Hardware Engagement (Key Down):** If the event is a key press, the Orchestrator identifies the specific key code (e.g., 'W', 'A', 'S', 'D', or the Arrow Keys). It then updates the corresponding boolean flag within the `InputLedger`'s key map to `true`, indicating active human intent.
5.  **Hardware Disengagement (Key Up):** Conversely, if the event is a key release, the Orchestrator locates the corresponding flag in the `InputLedger` and sets it to `false`.
6.  **Completion:** Once the queue is drained, the Orchestrator yields control back to the Sovereign, leaving behind a perfectly updated `InputLedger` that reflects the exact state of the keyboard at that precise millisecond.

### Section 3: The World Update Branch (Physics & Simulation)

This section details the core simulation of the "Chaos Maze." It strictly adheres to the principle of separating pure mathematical calculation (Transformers) from state mutation (Mutators), all governed by a sequential chain of command (Orchestrators).

#### 3.1 The World Ledgers (Data Structures)
The `WorldLedger` is the master repository of the simulation's state. It is a strictly passive, flat data structure, devoid of any logic or methods. It is composed of the following foundational ledgers:

*   **`Vector2D`**: The mathematical primitive, containing `x` and `y` floating-point values.
*   **`AABB` (Axis-Aligned Bounding Box)**: The spatial primitive for collision, containing `x`, `y` (top-left coordinate), `width`, and `height`.
*   **`TankData`**: The ledger for a combatant. It records `position` (`Vector2D`), `angle` (in radians), `speed`, `health`, `bulletCooldown`, and its physical `boundingBox` (`AABB`).
*   **`BulletData`**: The ledger for a projectile. It records `position`, `velocity` (both `Vector2D`), an `isActive` boolean (to manage the pre-allocated object pool without expensive memory reallocation), its `boundingBox`, and an `ownerID` (to prevent self-inflicted damage).
*   **`LevelData`**: The architectural blueprint of the arena, containing a collection (e.g., a `std::vector`) of indestructible wall `AABB`s.
*   **`WorldLedger` (The Container)**: Holds the specific instances: `player1` (`TankData`), `player2` (`TankData`), `bulletPool` (an array of `BulletData`), and the `maze` (`LevelData`).

#### 3.2 The Mathematician (The Transformers)
The Transformers are our pure, stateless specialists. They possess no memory of previous frames and hold no references to the ledgers. They simply receive data, perform the calculations mandated by the project specification, and return a result.

*   **`KinematicsTransformer`**: The master of motion.
    *   *Method - `calculateDisplacement(speed, angle, deltaTime)`*: Utilises standard trigonometry (`cos(angle)` for the X-axis, `sin(angle)` for the Y-axis) multiplied by `speed` and `deltaTime` to return a `Vector2D` representing the exact positional shift for this frame.
*   **`CollisionTransformer`**: The master of spatial awareness.
    *   *Method - `isIntersecting(AABB a, AABB b)`*: Evaluates the boundaries of two boxes. Returns `true` if they overlap on both the X and Y axes.
    *   *Method - `calculateSurfaceNormal(AABB moving, AABB static)`*: Determines which face of a static object was struck by calculating the shallowest axis of penetration. Returns a unit `Vector2D` representing the surface normal (e.g., `(0, -1)` for a top-face impact).
*   **`ReflectionTransformer`**: The master of ballistics.
    *   *Method - `calculateBounceVelocity(oldVelocity, normal)`*: Implements the precise reflection formula required by the specification: $\vec{V}_{new} = \vec{V}_{old} - 2(\vec{V}_{old} \cdot \vec{n})\vec{n}$. It calculates the dot product, scales the normal, and returns the new `Vector2D` trajectory.

#### 3.3 The State Representatives (Mutators)
The Mutators are the *only* entities authorised to alter the ledgers. They are instantiated with a direct reference to a specific piece of data (e.g., a single `TankData` struct) and provide a strictly controlled interface for modifying it.

*   **`TankMutator`**: The authorised agent for a tank.
    *   *Methods*: `applyDisplacement(Vector2D)` (updates both the logical position and the `AABB` coordinates), `setRotation(float)`, `reduceCooldown(float)`, and `takeDamage()` (decrements health).
*   **`BulletMutator`**: The authorised agent for a projectile.
    *   *Methods*: `applyDisplacement(Vector2D)`, `setVelocity(Vector2D)`, `activate(Vector2D startPos, Vector2D initialVel)`, and `deactivate()` (sets the `isActive` flag to false and moves the `AABB` safely off-screen).

#### 3.4 `WorldUpdateOrchestrator` (The Assembly Line Algorithm)
The `WorldUpdateOrchestrator` is the foreman of the physics engine. It receives the `InputLedger` and `TimeLedger` as read-only directives, and is granted mutable access to the `WorldLedger`. It does not perform calculations itself; rather, it sets up the Mutators and commands its Sub-Orchestrators in a strict, unyielding sequence.

**The High-Level Algorithm (`main` method):**

1.  **Resource Consolidation:** The Orchestrator instantiates the pure Transformers (`KinematicsTransformer`, `CollisionTransformer`, `ReflectionTransformer`) once, to be shared amongst its subordinates.
2.  **Commissioning the Agents:** It instantiates the Mutators for the current frame, binding `p1Mutator` to `WorldLedger.player1`, `p2Mutator` to `WorldLedger.player2`, and creating a list of `BulletMutators` bound to the active elements of the `bulletPool`.
3.  **Phase 1: Tank Manoeuvres:** It delegates to the `TankMovementOrchestrator`, passing the inputs, the time, the kinematics mathematician, and the `p1Mutator`. It then repeats this delegation for `p2Mutator`.
4.  **Phase 2: Ballistic Trajectories:** It iterates through the active `BulletMutators`, delegating each to the `BulletMovementOrchestrator` alongside the time and kinematics mathematician.
5.  **Phase 3: Conflict Resolution:** With all entities moved to their new theoretical positions, it delegates to the `CollisionResolutionOrchestrator`. It passes the collision and reflection mathematicians, all active mutators, and the read-only `LevelData`. This subordinate is tasked with detecting overlaps and commanding the mutators to bounce, halt, or take damage accordingly.

### 3.5 The Movement Sub-Orchestrators

These specialists are tasked with the pure application of kinematics. They read the current state, consult the mathematicians for the correct trajectories, and command the mutators to update the physical ledgers.

#### 3.5.1 `TankMovementOrchestrator` (The Driver's Algorithm)
This specialist acts as the driver and gunner of the tank. It reads the `InputLedger` to discern the player's orders, consults the `TimeLedger` to understand how much time has passed, and uses the `KinematicsTransformer` to calculate the resulting physical displacement. It then issues commands to the `TankMutator`.

**The High-Level Algorithm (`main` method):**

1.  **Intent Interrogation:** The Orchestrator reads the `InputLedger` specific to the tank it is currently commanding (e.g., checking 'W', 'A', 'S', 'D' for Player 1, or the Arrow Keys for Player 2).
2.  **Rotational Command:** If a turning key is depressed, it calculates the new angle (adding or subtracting a fixed rotational speed scaled by $\Delta t$) and commands the `TankMutator` to `setRotation()`.
3.  **Throttle Command:** If a forward or backward key is depressed, it sets the tank's internal speed variable (e.g., to maximum forward velocity or reverse velocity). If no throttle key is pressed, it sets the speed to zero.
4.  **Kinematic Delegation:** It passes the tank's current speed, its newly updated angle, and the `deltaTime` to the `KinematicsTransformer`. The pure mathematician returns a `Vector2D` representing the exact $X$ and $Y$ displacement for this frame.
5.  **Displacement Command:** It commands the `TankMutator` to `applyDisplacement()`, physically moving the tank's centre point and its bounding box to the new coordinates.
6.  **Weaponry Maintenance (Cooldown):** It commands the `TankMutator` to `reduceCooldown()` by the elapsed $\Delta t$, ensuring the main gun is prepared for the next firing order. *(Note: The actual spawning of a bullet, should the firing key be depressed and the cooldown clear, is handled by activating a dormant `BulletMutator` from the pool).*

#### 3.5.2 `BulletMovementOrchestrator` (The Ballistics Algorithm)
This specialist is far simpler, as a bullet in flight requires no further input from the player. It is a slave to its initial velocity and the relentless ticking of the clock. It requires only the `TimeLedger`, the `KinematicsTransformer`, and the `BulletMutator`.

**The High-Level Algorithm (`main` method):**

1.  **Status Verification:** The Orchestrator first queries the `BulletMutator` to ensure the projectile is currently active. If it is dormant (waiting in the object pool), the Orchestrator immediately returns, saving valuable CPU cycles.
2.  **Kinematic Delegation:** For an active bullet, it passes the bullet's current velocity vector and the `deltaTime` to the `KinematicsTransformer`. The mathematician scales the velocity by the time elapsed, returning the precise `Vector2D` displacement for this frame.
3.  **Displacement Command:** It commands the `BulletMutator` to `applyDisplacement()`, advancing the projectile along its trajectory.

### 3.6 The Collision Resolution Sub-Orchestrator

This overarching specialist acts as the chief umpire of the game. It does not perform the mathematical checks itself, nor does it directly alter the ledgers. Instead, it coordinates three highly specialised task forces, passing them the necessary pure mathematicians (`CollisionTransformer`, `ReflectionTransformer`) and the authorised state agents (`TankMutator`, `BulletMutator`).

#### 3.6.1 `TankWallCollisionOrchestrator` (The Blocking Algorithm)
This specialist ensures that our heavy armour cannot phase through solid masonry. It requires the `CollisionTransformer`, a `TankMutator`, and read-only access to the `LevelData`.

**The High-Level Algorithm (`main` method):**

1.  **The Sweep:** The Orchestrator iterates through every indestructible wall `AABB` defined within the `LevelData`.
2.  **Intersection Interrogation:** For each wall, it delegates to the `CollisionTransformer`, passing the tank's `AABB` and the wall's `AABB` to the `isIntersecting()` method.
3.  **The Correction Command:** If the pure mathematician returns `true` (indicating an overlap), the Orchestrator calculates the minimum translation vector—the shortest distance required to push the tank out of the wall. 
4.  **State Mutation:** It immediately commands the `TankMutator` to `applyDisplacement()` using this correction vector, effectively halting the tank flush against the brickwork. This process is repeated for both Player 1 and Player 2.

#### 3.6.2 `BulletWallCollisionOrchestrator` (The Reflection Algorithm)
This is the artillery specialist, responsible for executing the bouncing physics mandated by the specification. It requires both the `CollisionTransformer` and the `ReflectionTransformer`, alongside a `BulletMutator` and the `LevelData`.

**The High-Level Algorithm (`main` method):**

1.  **The Sweep:** Similar to the tank resolver, it iterates through the `LevelData` walls for the given active bullet.
2.  **Intersection Interrogation:** It asks the `CollisionTransformer` if the bullet's `AABB` intersects the wall's `AABB`.
3.  **Surface Analysis:** Upon a confirmed hit, it delegates to the `CollisionTransformer`'s `calculateSurfaceNormal()` method to determine exactly which face of the wall was struck (returning a normal vector, $\vec{n}$).
4.  **Ballistic Calculation:** It passes the bullet's current velocity and the newly acquired surface normal $\vec{n}$ to the `ReflectionTransformer`. The mathematician applies the formula $\vec{V}_{new} = \vec{V}_{old} - 2(\vec{V}_{old} \cdot \vec{n})\vec{n}$ and returns the precise bounce trajectory.
5.  **State Mutation:** The Orchestrator commands the `BulletMutator` to `setVelocity()` with this new vector. It also applies a minor positional correction to ensure the bullet is pushed slightly out of the wall, preventing it from becoming trapped inside the masonry on the subsequent frame.

#### 3.6.3 `BulletTankCollisionOrchestrator` (The Damage Algorithm)
This specialist adjudicates combat. It determines if a projectile has successfully struck an enemy combatant. It requires the `CollisionTransformer`, the `BulletMutator` of the projectile in question, and the `TankMutator` of the potential target.

**The High-Level Algorithm (`main` method):**

1.  **Friendly Fire Verification:** Before any mathematics are performed, the Orchestrator checks the bullet's `ownerID`. If the bullet belongs to the target tank, the check is aborted to prevent self-inflicted damage.
2.  **Intersection Interrogation:** It delegates to the `CollisionTransformer` to check for an overlap between the bullet's `AABB` and the enemy tank's `AABB`.
3.  **Combat Resolution:** If a hit is confirmed, the Orchestrator issues two immediate commands:
    *   It commands the enemy `TankMutator` to `takeDamage()`, decrementing its health ledger.
    *   It commands the `BulletMutator` to `deactivate()`, instantly removing the projectile from the active simulation and returning it to the dormant pool.

### Section 4: The Rendering (Visual Exhibition)

This section details the final phase of our Game loop. It is strictly an observer of the game; it is granted only read-only (`const`) access to the `WorldLedger`. Its sole purpose is to translate the physical state of the arena into a visual spectacle for the combatants.

#### 4.1 The Display Ledger (Data Structure)
The `DisplayLedger` is our hardware manifest. Unlike the `WorldLedger`, which holds logical game state, this ledger holds the low-level memory addresses required to communicate with the operating system's graphics hardware (via a framework such as SDL2 or SFML). It is a passive struct containing:

*   **`windowHandle`**: A pointer to the operating system's application window.
*   **`renderContext`**: A pointer to the hardware-accelerated rendering canvas (e.g., `SDL_Renderer*`).
*   **Texture Assets**: A collection of pointers to the graphical sprites loaded into the video memory. Specifically, it holds `tankTexture`, `turretTexture`, `wallTexture`, and `bulletTexture`.

#### 4.2 The Visual Specialists
Before we can issue drawing commands, we must bridge the gap between the pure mathematics of our physics engine and the specific requirements of our rendering API. We achieve this through two highly specialised actors: one pure mathematician, and one authorised painter.

**4.2.1 `VisualTransformTransformer` (The Geometry Mathematician)**
Rendering frameworks typically require angles to be expressed in degrees, whereas our `KinematicsTransformer` rightly operates using standard C++ radians. Furthermore, the project specification explicitly demands that we *"Rotate sprites (Tank Body vs. Turret) around their center."* This pure, stateless Transformer handles these visual conversions.

*   *Method - `radiansToDegrees(float radians)`*: A pure function that multiplies the input by $(180.0 / \pi)$, returning the precise angle in degrees required by the rendering API.
*   *Method - `calculateSpriteCentre(AABB box)`*: A pure function that takes a bounding box and returns a `Vector2D` representing its exact local centre point (`width / 2.0f`, `height / 2.0f`). This ensures our tanks rotate smoothly on their axles rather than swinging wildly from their top-left corners.

**4.2.2 `CanvasMutator` (The Authorised Painter)**
This is the only entity in our entire architecture authorised to alter the pixels on the screen. It holds a direct reference to the `DisplayLedger` and wraps the low-level C-style calls of our chosen framework into an object-oriented interface.

*   *Method - `clearScreen()`*: Commands the graphics card to wipe the previous frame from the back-buffer, preparing a fresh canvas.
*   *Method - `drawSprite(texture, destRect, angleDegrees, centre)`*: The workhorse of the visual engine. It takes a texture pointer from the ledger, the physical `AABB` from the `WorldLedger`, and the calculated angle and centre from our Transformer, and commands the hardware to stamp the sprite onto the buffer.
*   *Method - `drawText(string, x, y)`*: A specialised command for rendering the Heads-Up Display (HUD), translating standard strings into visual typography at the specified screen coordinates.
*   *Method - `presentScreen()`*: The final command of the frame. It swaps the hidden back-buffer onto the 

#### 4.3 `RenderOrchestrator` (The Exhibition Algorithm)
The `RenderOrchestrator` is the chief director of our visual output. It is granted mutable access to the `DisplayLedger` (to alter the screen buffer) but is strictly restricted to read-only (`const`) access to the `WorldLedger`. It cannot accidentally move a tank whilst trying to paint it. Its duty is to enforce the "Painter's Algorithm"—ensuring the background is drawn first, followed by the actors, and finally the interface overlay.

**The High-Level Algorithm (`main` method):**

1.  **Commissioning the Painter:** The Orchestrator instantiates the `CanvasMutator`, binding it to the `DisplayLedger` for this specific frame. It also instantiates the pure `VisualTransformTransformer` to handle the necessary geometry conversions.
2.  **Preparing the Canvas:** It commands the `CanvasMutator` to `clearScreen()`, wiping away the remnants of the previous frame to provide a pristine black backdrop.
3.  **Phase 1: The Set Dressing:** It delegates to the `MapRenderOrchestrator`, passing the read-only `LevelData`, the `CanvasMutator`, and the wall texture pointer.
4.  **Phase 2: The Actors:** It delegates to the `EntityRenderOrchestrator`, passing the read-only `TankData` for both players, the `bulletPool`, the `VisualTransformTransformer`, the `CanvasMutator`, and the relevant texture pointers.
5.  **Phase 3: The Overlay:** It delegates to the `HUDRenderOrchestrator`, passing the read-only `TankData` (specifically for health and score) and the `CanvasMutator`.
6.  **The Grand Reveal:** With all elements painted onto the hidden back-buffer, it issues the final command of the frame: instructing the `CanvasMutator` to `presentScreen()`, swapping the buffer onto the physical monitor.

#### 4.4 The Exhibition Sub-Orchestrators
These three specialists handle the specific logic of translating game data into visual commands. They do not communicate with the hardware directly; they merely issue instructions to the `CanvasMutator`.

**4.4.1 `MapRenderOrchestrator` (The Set Dresser's Algorithm)**
This specialist is responsible for painting the indestructible maze. As walls do not rotate, its task is highly efficient.
1.  **The Sweep:** It iterates through the collection of wall `AABB`s within the `LevelData`.
2.  **The Stamp:** For each wall, it commands the `CanvasMutator` to `drawSprite()`, passing the wall texture, the `AABB` for position and scale, an angle of `0.0f`, and a default centre point.

**4.4.2 `EntityRenderOrchestrator` (The Portrait Artist's Algorithm)**
This specialist paints the dynamic elements of the simulation. It must consult the mathematician to ensure sprites are rotated correctly around their axles, fulfilling the specification's requirement for 2D transformations.
1.  **Tank Rendering (Player 1 & 2):** 
    *   It passes the tank's `AABB` to the `VisualTransformTransformer` to calculate the exact local `centre` point.
    *   It passes the tank's `angle` (in radians) to the Transformer to receive the `bodyAngleDeg` (in degrees).
    *   It commands the `CanvasMutator` to `drawSprite()` for the tank body using these calculated values.
    *   *High-Distinction Bonus:* It repeats the angle conversion for the `turretAngle` and issues a second `drawSprite()` command to layer the turret texture perfectly over the body's centre point.
2.  **Munitions Rendering:**
    *   It iterates through the `bulletPool`.
    *   If a bullet's `isActive` flag is true, it calculates its centre point and commands the `CanvasMutator` to draw the bullet texture at the projectile's current `AABB` coordinates.

**4.4.3 `HUDRenderOrchestrator` (The Scorekeeper's Algorithm)**
This specialist ensures the combatants are aware of their standing, fulfilling the HUD requirement of the specification.
1.  **String Formatting:** It reads the `health` and `score` integers from Player 1's `TankData` and formats them into a readable string (e.g., `"P1 Health: 3 | Score: 150"`). It repeats this for Player 2.
2.  **Typography Command:** It commands the `CanvasMutator` to `drawText()`, placing Player 1's string at the top-left coordinates of the screen, and Player 2's string at the top-right.
