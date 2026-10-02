# cub3D - 42 School Project

A raycasting 3D game engine in C using minilibx, inspired by Wolfenstein 3D.

## Overview

This project implements a basic 3D renderer using raycasting techniques. It reads a map file, displays a first-person view of a maze-like environment, and allows the player to move around using keyboard controls. It's part of the 42 school curriculum and demonstrates understanding of graphics programming, mathematics (raycasting algorithm), and event handling.

## Features

### 3D Rendering
- Raycasting algorithm for 3D perspective
- Textured walls (4 different textures for each direction)
- Configurable floor and ceiling colors
- Smooth movement and rotation

### Player Controls
- `W` - Move forward
- `A` - Move backward
- `S` - Strafe left
- `D` - Strafe right
- `←` - Rotate camera left
- `→` - Rotate camera right
- `ESC` - Exit game
- Close button (X) - Exit game

### Map Parsing
- Configuration file parsing (.cub extension)
- Texture path configuration
- Floor and ceiling color configuration (RGB)
- Map validation (closed borders, valid characters, player spawn)

## Project Structure

```
cub3d/
├── src/                        # Source files
│   ├── main.c                 # Entry point and initialization
│   ├── map_reader.c           # Map file reading
│   ├── map_validate.c         # Map validation
│   ├── map_textures.c         # Texture loading
│   ├── map_utils.c            # Map utilities
│   ├── map_complete.c         # Map completion/padding
│   ├── exit.c                 # Cleanup and exit handling
│   └── draw_and_render/       # Rendering subsystem
│       ├── raycasting.c       # Raycasting algorithm
│       ├── rendering.c        # Main render loop
│       ├── draw.c             # Drawing primitives
│       ├── player.c           # Player movement and input
│       └── utils.c            # Rendering utilities
├── inc/                        # Header files
│   └── cub3d.h                # Main declarations
├── maps/                       # Map files
│   ├── example.cub            # Example map
│   ├── basic.cub              # Basic test map
│   └── error*.cub             # Error test cases
├── textures/                   # Texture files
│   ├── wall1.xpm              # Wall textures
│   ├── floor.xpm              # Floor texture
│   └── ...
├── obj/                        # Compiled objects (generated)
├── .deps/                      # Dependencies (generated)
├── Makefile                   # Build configuration
└── cub3D                      # Executable (generated)
```

## Dependencies

This project depends on:
- [libraryC](https://github.com/Davter17/MyLibrary.git) - Custom library with libft, ft_printf, and get_next_line
- [minilibx-linux](https://github.com/42Paris/minilibx-linux.git) - Simple graphics library

Both are automatically cloned during compilation.

## Compilation

### Basic compilation
```bash
make
```
Clones dependencies (if needed) and compiles the game.

### Clean build
```bash
make re
```
Removes all compiled files and recompiles everything.

### Cleaning
```bash
make clean    # Removes obj/ directory
make fclean   # Removes obj/, .deps/, and cub3D binary
```

## Usage

```bash
./cub3D <map_file.cub>
```

### Map File Format

Map files must have the `.cub` extension and contain:

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 100,150,180

1111111111
1000000001
1P00000001
1000000001
1111111111
```

#### Configuration Lines
- `NO` - North wall texture path
- `SO` - South wall texture path
- `WE` - West wall texture path
- `EA` - East wall texture path
- `F` - Floor color (RGB format: R,G,B)
- `C` - Ceiling color (RGB format: R,G,B)

#### Map Characters
- `1` - Wall
- `0` - Empty space
- `N` - Player spawn (facing North)
- `S` - Player spawn (facing South)
- `W` - Player spawn (facing West)
- `E` - Player spawn (facing East)
- ` ` - Empty space (outside map)

## Implementation Details

### Raycasting Algorithm
- DDA (Digital Differential Analysis) algorithm for ray-wall intersection
- One ray per vertical column of the screen
- Perspective correction for wall heights
- Texture mapping based on hit position

### Map Parsing
- Header parsing for textures and colors
- Map validation (closed borders, single player spawn)
- Map padding for consistent dimensions
- Space validation (must be surrounded by walls)

### Memory Management
- Careful allocation and deallocation
- No memory leaks (verified with Valgrind)
- Proper cleanup on errors and exit
- Safe image and window destruction

## Code Quality

- Complies with 42 school's norminette standards
- No memory leaks (verified with Valgrind)
- Handles edge cases and error conditions
- Clean separation of concerns
- Proper resource management

## Requirements

- GCC compiler
- Make
- X11 development libraries (`libx11-dev`, `libxext-dev`)
- Unix-like environment (Linux, macOS, or WSL)

## Authors

- **Mario Pico** (@Davter17)
- **Marta Cuesta** (@mcuesta-)

## License

This project is part of the 42 school curriculum and follows its academic guidelines.
