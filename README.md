# 🐍 Snake Game in C (OpenGL + FreeGLUT)

A simple yet visually enhanced **Snake Game** written in **C**, using **OpenGL** and **FreeGLUT** for graphics rendering.  
This project demonstrates core game logic, rendering pipelines, keyboard input handling, and texture mapping — all built from scratch.

---

## 🎮 Game Overview

Control a snake to eat apples (`+`) that appear randomly on the board.  
Each apple increases the snake’s length and score.  
The game ends if the snake collides with a wall or itself.  
After a short pause, the game automatically restarts.

---

## 🧠 Features

- 🟩 Fully coded in **C**
- 🧩 Uses **OpenGL** and **FreeGLUT**
- 🍎 Random apple generation
- 🐍 Snake growth logic
- 💥 Wall & self-collision detection
- 🔁 Auto restart on game over
- 🎨 Textured graphics via `snake_tileset.c`

---

## 🛠️ Requirements

### 🔹 Windows
- **MinGW** or **TDM-GCC** compiler  
- **FreeGLUT** development library  
- **OpenGL** (`opengl32`, `glu32`, `gdi32`, `winmm`)

---

## ⚙️ Compilation & Execution

### 🧩 Step 1 — Compile:
```bash
gcc Snake.c -o snake_game -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
```

# ⌨️ Controls
| Key       | Action       |
| --------- | ------------ |
| **W / ↑** | Move Up      |
| **S / ↓** | Move Down    |
| **A / ←** | Move Left    |
| **D / →** | Move Right   |
| **R**     | Restart Game |


---

# 🧱 How It Works
🕹️ Board Setup

The 1D array board[] represents the game grid.

Borders (#) are generated during setup.

## 🐍 Snake

Defined by struct Snake, containing:

length of the snake

Array of body coordinates (x, y)

 ## 🍎 Apples

Defined by struct Apple, each with:

Position (x, y)

Eaten state

## 🎨 Rendering

Uses OpenGL quads for each tile (snake, walls, apples).

Tiles are mapped from the included snake_tileset.c.

## 🏆 Scoring

Each apple eaten = +100 points

Score = (snake length - 1) × 100

Displayed at the top of the screen

---
# 💡 Future Improvements

### 🔊 Add sound effects

### ⚙️ Add difficulty levels

### 🏁 Create a start menu or pause feature

### 💾 Save high scores to file

### 🐧 Port to Linux/macOS using SDL2 or GLFW
