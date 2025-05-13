# Sudoku Game with SFML

A Sudoku game implementation using SFML graphics library.

## Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler
- SFML 2.5 or higher

## Building the Project

```bash
# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

## Project Structure

- `src/` - Source files
- `include/` - Header files
- `resources/` - Game resources
  - `audio/` - Sound effects and music files
  - `fonts/` - Font files
  - `images/` - Image assets
    - `game/` - In-game graphics (board, numbers, icons)
    - `menu/` - Menu and UI graphics
- `build/` - Build output directory

## Running the Game

After building, you can run the game from the build directory:

```bash
./Sudoku
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.
