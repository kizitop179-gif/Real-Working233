# 11v11 Football Game with SFML

A full-featured 2-team football (soccer) game with 11 players per team, built with C++ and SFML!

## Features
- ⚽ **11 Players Per Team** (4-3-3 Formation)
- **Full Football Pitch** with markings
- **Realistic Player Movement** with physics
- **Ball Physics** with collision detection
- **Score Tracking** and Game Timer
- **Multiple Teams** - Blue vs Red
- **Smooth Controls** and Gameplay

## Game Formation (4-3-3)
- 1 Goalkeeper
- 4 Defenders
- 3 Midfielders
- 3 Forwards

## Controls

### Team A (Blue) - Left Side
- **W** / **S** - Move Up/Down
- **A** / **D** - Move Left/Right
- **Space** - Pass/Shoot
- **Click** - Select Player

### Team B (Red) - Right Side
- **Up Arrow** / **Down Arrow** - Move Up/Down
- **Left Arrow** / **Right Arrow** - Move Left/Right
- **Enter** - Pass/Shoot
- **Click** - Select Player

### General
- **R** - Reset Game & Scores

## How to Play

1. **Click on a player** to select them (shown with yellow outline)
2. **Use arrow keys or WASD** to move the selected player
3. **Press Space or Enter** to pass/shoot the ball
4. **Score goals** by getting the ball into the opponent's goal area
5. **Pass between players** to move up the field
6. **Time increases** as you play

## Building the Project

### Prerequisites
- C++17 or later
- SFML 2.5+
- CMake 3.16+

### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
./bin/Football11v11
```

### Windows
```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
.\bin\Release\Football11v11.exe
```

## Game Rules
- Score by getting the ball into the opponent's goal area (center portion)
- Each team has 11 players in a standard 4-3-3 formation
- Players can move freely across the pitch
- Ball bounces off walls and players
- Game timer tracks elapsed time

## Project Structure
```
├── CMakeLists.txt      # Build configuration
├── src/
│   ├── main.cpp        # Entry point
│   ├── Game.h/.cpp     # Main game class
│   ├── Team.h/.cpp     # Team management (11 players)
│   ├── Player.h/.cpp   # Individual player
│   └── Ball.h/.cpp     # Ball physics
└── README.md           # This file
```

## Future Enhancements
- AI-controlled players
- Tactical formations
- Special moves/tricks
- Sound effects and music
- Improved graphics with sprites
- Replay system
- Tournament mode
- Player stats tracking

## Tips
- Click on defensive players to clear the ball
- Use forwards to attack and score
- Pass between midfielders for better positioning
- Control the ball near the goal to score

Enjoy the game! ⚽🎮
