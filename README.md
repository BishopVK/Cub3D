# Cub3D

## Grade

| **Score** | **Description** |
| --------- | ----- |
| <p align="center"><img width="200px" alt="170px" src="https://github.com/BishopVK/Cub3D/img/Score_110.png"></p> | **Mandatory part + 2 of 5 Bonus**   |

## Description
Cub3D is a graphics project inspired by the classic game Wolfenstein 3D. It uses raycasting techniques to create a 3D experience from a 2D map. This project implements a basic rendering engine using the MLX42 library.

## Features
- 3D rendering using raycasting techniques  
- Player movement using keyboard and mouse  
- Customizable wall textures  
- Configurable floor and ceiling colors  
- Map parsing system with validation  

## Requirements
- GCC or Clang  
- Make  
- CMake  
- GLFW library  

## Installation

**Clone the repository**
```bash
git clone https://github.com/BishopVK/Cub3D.git  
cd Cub3D
```

**Build the project**
```bash
make
```

## Usage
```bash
./cub3D maps/map.cub
```

## Map File Format (`.cub`)
The map file must contain:

- Paths to textures for the walls (NO, SO, WE, EA)  
- RGB colors for the floor (F) and ceiling (C)  
- A map composed of the following characters:  
  - `'0'`: Empty space  
  - `'1'`: Wall  
  - `'N', 'S', 'E', 'W'`: Player's starting position and direction  

**Example:**
```
NO ./path_to_the_north_texture.png  
SO ./path_to_the_south_texture.png  
WE ./path_to_the_west_texture.png  
EA ./path_to_the_east_texture.png  

F 220,100,0  
C 225,30,0  

        1111111111111111111111111  
        1000000000110000000000001  
        1011000001110000000000001  
        1001000000000000000000001  
111111111011000001110000000000001  
100000000011000001110111111111111  
11110111111111011100000010001  
11110111111111011101010010001  
11000000110101011100000010001  
10000000000000001100000010001  
10000000000000001101010010001  
11000001110101011111011110N0111  
11110111 1110101 101111010001  
11111111 1111111 111111111111  
```

## Controls
- `W`, `A`, `S`, `D`: Move the player  
- Left/Right Arrow Keys: Rotate the camera  
- Mouse: Rotate the camera  
- `ESC`: Exit the game  

## Project Structure
- `src/`: Main source code  
- `parse/`: Map parsing modules  
- `flood_fill/`: Map validation using flood fill  
- `init/`: Game and player initialization  
- `game_engine/`: Game engine (input, render, raycasting)  
- `lib/`: External libraries (MLX42)  
- `maps/`: Example map files  

## Credits
Developed by:

- **BishopVK**  
- **[Daniel Jimenez Graindorge - BishopVK](https://github.com/BishopVK)**
- **[Sergio Fernández Fernández - zenix-s](https://github.com/zenix-s)**