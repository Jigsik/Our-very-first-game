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
- SFML 2.5/2.6 development libraries

Current WSL preflight:

- `g++`: available
- `cmake`: missing
- `pkg-config sfml-graphics`: missing
- `libsfml-dev`: not installed
- apt candidate exists, but sudo needs an interactive password

## Build

```bash
cd spikes/sfml-cmake
cmake -S . -B build
cmake --build build
./build/sfml_spike
```

## Recommendation

Maybe candidate, but blocked on native dependencies in the current environment. Continue only if we intentionally want C++/SFML as part of the learning goal. For low-prompt AI iteration, this has higher friction than the web spike.
