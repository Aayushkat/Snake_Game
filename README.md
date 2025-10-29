Classic Snake Game

This is a classic Snake game implementation developed in C, utilizing the OpenGL Utility Toolkit (GLUT) for graphics rendering and a console-based approach for game logic management.

The game features a fixed-size grid, wall and self-collision detection, and score tracking based on the snake's length.

🚀 Features

Grid-Based Movement: Smooth movement of the snake across a defined grid.

Collision Detection: Checks for collision with the boundary walls and with the snake's own body.

Real-time Graphics: Uses OpenGL and GLUT to render the game world with tiled graphics.

Scoring System: Score increases as the snake eats apples.

Game Over/Restart: Automatic game restart after a short timeout following a game over event.

Input Handling: Supports both W/A/S/D and Arrow Keys for movement.

🛠️ Dependencies

To compile and run this project, you need a C compiler (like GCC) and the following graphics libraries:

OpenGL / GLU

FreeGLUT (or standard GLUT)

Windows API Libraries (winmm and gdi32 are required for the Windows functions used, like Sleep).

snake_tileset.c: This project relies on a file named snake_tileset.c which contains the texture/pixel data for rendering the game tiles. This file must be present in the project directory.

⚙️ Getting Started

Prerequisites

Ensure you have a C development environment (like MinGW or Visual Studio with GCC/G++) and the FreeGLUT library installed on your system.

Compilation

You can compile the game using the following command, as indicated in the source code comments. This command links the necessary libraries:

# Assuming your main file is named 'Snake.c'
gcc Snake.c -o final -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32


Running the Game

After successful compilation, run the generated executable:

./final


🎮 How to Play

Controls

The snake's movement can be controlled using two sets of keys:

Action

Keyboard Key

Move Up

W or Up Arrow

Move Down

S or Down Arrow

Move Left

A or Left Arrow

Move Right

D or Right Arrow

Restart Game

R

Game Objective

Guide the snake to eat the Apples (+ symbol).

Each apple eaten increases the snake's length and your score.

Avoid hitting the Walls (# symbol) or the Snake's own body.

Hitting a wall or the snake's body results in a Game Over.
