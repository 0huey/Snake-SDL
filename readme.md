### Snake

The classic snake game.

This was my introduction to SDL and C++

### Installation

- Download [SDL2-devel-*-VC](https://github.com/libsdl-org/SDL/releases)
- Extract it to `..\SDL` relative to the project folder
- Either
  - update your PATH to include SDL\lib\x64
  - hard link SDL2.dll with `MKLINK /H SDL2.dll ..\SDL\lib\x64\SDL2.dll`
- Build with MSVC `nmake`
