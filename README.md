# CTraining

This is personal project to train c++

\#Project dependencies

-SDL3 V.3.2.16

-SDL3\_Image V 3.2.4
-rapidjson https://github.com/Tencent/rapidjson/blob/master/readme.md
-Rider or visual studio 2022

* using https://youtu.be/QQzAHcojEKg?si=q06o6l21xq-HwEca for base reference

\#The Project

Space Invaders Clone (C++ / SDL3)
🛠 Development Branch: feat/space-invader
This branch contains the specific implementation of a Space Invaders clone, built on top of my custom-made C++ Game Engine. The primary goal of this project is to deepen my expertise in low-level systems engineering, memory management, and game architecture using C++20 and SDL3.

🎯 Project Objective
To leverage my custom-built Entity Component System (ECS) framework to create a faithful recreation of the classic arcade hit. This project serves as a technical "stress test" for the engine's core systems while practicing industry-standard development workflows.

⚙️ Branch Strategy & Workflow
To maintain a clean and professional codebase, I follow a strict Engine vs. Game separation:

Specific Logic: All code related to aliens, bunkers, and player scoring resides exclusively in this branch.

Engine Evolution: Any architectural improvements discovered during development (e.g., enhancements to the ECS, Input, or Collision systems) are committed separately and cherry-picked back into the main branch.

Modularity: The game acts as a standalone module that consumes the engine's API, ensuring the core framework remains generic.

👾 Implemented Mechanics
To ensure a high-quality clone, the following classic mechanics are being implemented:

1. The Alien Horde (Grid Movement)
Collective Movement: 55 aliens (11x5 grid) moving as a single unit.

Difficulty Scaling: The horda's movement speed increases as the number of remaining aliens decreases.

The "Drop & Flip": When any alien touches the screen boundary, the entire grid shifts downward and reverses horizontal direction.

2. Strategic Defense (Destructible Bunkers)
Pixel-Perfect Erosion: Four defensive bunkers that degrade as they take fire from both the player and the aliens.

Dynamic Collision: Utilizing sub-division or bitmasking to allow projectiles to "carve" through the defenses.

3. Combat & Projectile Systems
Bullet Pooling: A memory-efficient Object Pool for projectiles to avoid frequent heap allocations/deallocations.

Player Arsenal: Controlled fire rate with a single projectile limit to maintain original arcade tension.

Alien Bombing: Randomized firing logic from the bottom-most aliens of each column.

4. Scoring & Mystery Ship
Point Tiers: Different point values for Top, Middle, and Bottom alien rows.

UFO (Mystery Ship): A random-spawn high-value target that traverses the top of the screen.

💻 Technical Highlights (My Focus)
Bitmask Collision Channels: Implementing a custom collision filtering system inspired by Unreal Engine’s collision channels.

Data-Driven Sprites: Using the Flyweight Pattern to ensure that 55 aliens share a single memory resource for their pixel data.

Custom ECS: Managing game state through a specialized Entity Component System for high performance and decoupled logic.

