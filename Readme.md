# Labyrinth Treasure Hunt



<br />

<div align="center">

[![forthebadge made-with-c++](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://github.com/yourusername/labyrinth-treasure-hunt)
<br />
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-no-red.svg)](https://github.com/yourusername/labyrinth-treasure-hunt/graphs/commit-activity)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square)](https://github.com/yourusername/labyrinth-treasure-hunt/blob/master/LICENSE)

</div>

> Developed by Raoul Ammar Houssembay and Srijita Nandi as part of the Master's Program in Object-Oriented Programming C++ at Université Paris-Saclay (2023-2024), Labyrinth Treasure Hunt is a 3D maze exploration game where players navigate a labyrinth to find treasure while avoiding guards, showcasing practical application of C++, OpenGL, and FLTK.


https://github.com/Ammar434/Labyrinth_Treasure_Hunt/assets/50246683/9af0759f-fae9-41b1-99d5-1c8bded90f99

## Game Overview

The objective of this game is to navigate a complex 2D maze rendered in 3D, controlling a character called the "Hunter" using either the mouse or keyboard. Players must avoid obstacles and enemies, termed "Guards," who protect the labyrinth's treasure. Success involves reaching the treasure while surviving enemy attacks and overcoming environmental challenges.

## Folder Structure

    Labyrinth Treasure Hunt
    ├── Makefile            # Compilation scripts to build the game
    ├── bin                 # Contains binary and executable files
    ├── include             # Header files for the project
    ├── lib # Libraries and external dependencies
    ├    ├── OpenGL # OpenGL libraries specific to different platforms
    ├    ├── fltk # Fast Light Toolkit libraries for the GUI
    ├    ├── fmod # FMOD sound engine libraries for audio management  
    ├── modeles # 3D models used for game characters and items
    ├── sons # Sound files for game effects like background music and sound effects
    ├── src # Source files containing the game's main logic
    ├── textures # Image files used for texturing the game environment and elements
    └── README.md

### Platforms Used

- **C++**: Chosen for its performance and flexibility in game development.
- **OpenGL**: Utilized for rendering 2D and 3D vector graphics using hardware acceleration.
- **FLTK (Fast Light Toolkit)**: Employed for creating the game's graphical user interface, managing user inputs, and displaying UI elements.

## Labyrinthe Structure

The game's labyrinth, designed from a textual layout in a `.txt` file, involves parsing and placement of walls (`+` for vertical, `-` for horizontal), characters (`C` for the hunter, `G` for guards), and items (`T` for treasure, `X` for boxes). The labyrinth is dynamic, with elements positioned based on parsed data, creating a varied gameplay experience with each session.

## Gameplay Mechanics

### Hunter
- **Movement and Interaction**: Players control the Hunter, navigating through the maze, avoiding or utilizing obstacles for protection against Guard attacks.
- **Combat**: The Hunter can attack guards using fireballs, requiring precise aiming and timing.

### Guard
- **AI Behavior**: Guards switch between patrolling and attacking modes based on the Hunter's location. They use a simple AI to chase the Hunter or return to patrolling when the Hunter escapes their line of sight.
- **Combat**: Guards attack by shooting fireballs that can be dodged or blocked using the maze's layout.

## Technical Highlights

- **Parsing and Dynamic Placement**: The game's engine parses layout data and dynamically places game elements, facilitating a modular and scalable game architecture.
- **Inheritance and Polymorphism**: Utilizes OOP principles, allowing for extensible character behaviors and interactions.
- **Event-Driven Programming**: Handles user inputs and game events in a responsive manner.

## Building and Running


### Prerequisites

- **C++ Compiler**: GCC or Clang, capable of supporting C++17 standards.
- **Make**: A build automation tool required to automate the compilation process.

### Clone the Project

Clone the repository to get the source code on your local machine:

```shell
git clone https://github.com/yourusername/labyrinth-treasure-hunt.git
cd labyrinth-treasure-hunt
```

### Build the Project
```shell
make
```
### Run the Game
```shell
./bin/labh -l labyrinthe.txt -f -a
```



