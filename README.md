# Weak Point

A simple action game where you dash through endlessly spawning drones to kill them. But be careful to dash through their weak point! This game was made in under a week for the [Rutgers COGS Scarlet Game Jam 2022](https://itch.io/jam/scarlet-game-jam-fall-2022) (improvements will continue to be made). It is published on [itch.io](https://dan-and-suman.itch.io/weak-point)

## Controls/Tutorial

- WASD - move
- SPACE - dash
- Simply dash through the enemies along the dotted line while dodging their bullets

## Screenshots

## Build

### Windows

1. Clone repository
2. Install [CMake](https://cmake.org/)
3. Install the following deopendencies (in a location CMake can locate):
    * `sdl2`
    * `sdl2_image`
    * `sdl2_ttf`
    * `sdl2_mixer`
4. From the root of the project directory, create a `build` directory, and run `CMakeLists.txt` from there:
    * `mkdir build`
    * `cd build`
    * `cmake ..`
5. Or, if on unix, simply `make all` from the root directory
