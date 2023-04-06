# Ultra Super Space Rocks

A top-down view single player shooter game inspired by the classic Atari game, Asteroids. Created using C++ and the Raylib game development library.

By: Josh O’Neil, Gunveer Vilkhu, Imesh Nimsitha, Gurshawn Lehal, and Muhammed Syed

## How to Play

The player navigates through space by controlling a ship equipped with a ranged weapon. The aim of the game is to collect as many points as possible by avoiding and destroying enemy obstacles. Weapons can be upgraded by flying into powerup orbs during special times in the game.

## Controls

- Accelerate: `UP` or `W`
- Decelerate: `DOWN` or `S`
- Turn left: `LEFT` or `A`
- Turn right: `RIGHT` or `D`
- Shoot: `SPACE`
- Start game: `SPACE` or `ENTER`
- Pause game: `P`
- Exit game: `ESC`

## Installation Instructions

For Mac/Linux users:
`make setup`

For Windows users:
`mingw32-make setup`

To install any missing system-specific dependencies, please view the `docs\InstallingDependencies.md` file.  
If you are on a Linux machine, install all the corresponding dependencies:

```
sudo apt install libxcursor-dev
sudo apt install libxinerama-dev
sudo apt install libxi-dev
sudo apt install libx11-dev
sudo apt install libglu1-mesa-dev
sudo apt install libxrandr-dev
```

## Running Instructions

For Mac/Linux users:
`make`

For Windows users:
`mingw32-make`
