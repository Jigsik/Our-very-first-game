# Modern C++ / SFML Spike

Minimal CMake project for testing whether a modernized SFML route is worth continuing.

## What It Tests

- CMake project isolated from old Visual Studio files.
- Loading `The_Game/The_Game/Maps/mapa.txt`.
- Loading the old tileset and player image.
- Two local players.
- Split-screen views.
- Basic movement and shooting.

## Required Tools

- CMake 3.22+
- C++17 compiler
- SFML 3 development libraries

Current WSL preflight:

- `g++`: available
- `cmake`: available after Martin installed dependencies
- `pkg-config sfml-graphics`: 3.0.2
- `libsfml-dev`: installed

## Build

```bash
cd spikes/sfml-cmake
cmake -S . -B build
cmake --build build
./build/sfml_spike
```

## Recommendation

Maybe candidate. The native build now works with SFML 3, but this remains higher-friction than the web path for low-prompt AI iteration.
