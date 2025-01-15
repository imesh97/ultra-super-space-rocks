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

### Desktop Build

1. Clone the repository:

```bash
git clone https://github.com/imesh97/ultra-super-space-rocks.git
cd ultra-super-space-rocks
```

2. Initialize and update the raylib submodule:

```bash
git submodule init
git submodule update
```

3. Build raylib:

```bash
cd vendor/raylib/src
make PLATFORM=PLATFORM_DESKTOP
cd ../../..
```

### Web Build

1. Install Emscripten:

View instructions here: https://emscripten.org/docs/getting_started/downloads.html

Ensure installation to `~/emsdk`.

2. Ensure Emscripten is installed and activated:

```bash
cd ~/emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

## Running Instructions

### Desktop Build

```bash
make
```

The executable will be created based on your platform:

- Windows: Creates `ultrasuperspacerocks.exe`
- Linux: Creates `ultrasuperspacerocks`
- macOS: Creates `ultrasuperspacerocks.app`

### Web Build

```bash
make web
```

This generates:

- `ultrasuperspacerocks.html` - Main game page
- `ultrasuperspacerocks.js` - JavaScript support code
- `ultrasuperspacerocks.wasm` - WebAssembly binary
- `ultrasuperspacerocks.data` - Game resources

After building for web:

1. Start a local web server:

```bash
python3 -m http.server 8080
```

2. Open a web browser and navigate to:

```
http://localhost:8080/ultrasuperspacerocks.html
```

Note: Due to browser security restrictions, the game must be served through a web server.

## Build Configuration

Build modes:

- Debug build: `make BUILD_MODE=DEBUG`
- Release build: `make BUILD_MODE=RELEASE` (default)

Platform options:

- Desktop build: `make PLATFORM=PLATFORM_DESKTOP` (default)
- Web build: `make PLATFORM=PLATFORM_WEB`

Clean build:

```bash
make clean   # Removes all build artifacts
```
