# Raw Renderer

A raw Windows.h exclusive OpenGL loader written in C. This project provides low-level rendering utilities with custom math functions and OpenGL context management without external dependencies.

## Overview

Raw Renderer is a minimalist OpenGL rendering framework designed for Windows platforms. It directly uses the Windows API (`windows.h`) for window creation, context management, and event handling, paired with custom math utilities for graphics calculations.

## Features

- Windows-native OpenGL loader
- Custom math library (sqrt, abs, min, max, trigonometric functions)
- Direct Windows API integration
- Minimal external dependencies

## Build Requirements

- **mingw-w64** - GCC-based compiler for Windows
  - Install via MSYS2, Scoop, Chocolatey, or from [mingw-w64.org](https://www.mingw-w64.org/)
  - Ensure `gcc`, `make`, and standard tools are available in PATH

## Building

```bash
.\build
```

## Requirements

- Windows OS (Only tested on windows 11)
- OpenGL 4.6 compatible graphics card
- mingw-w64 C compiler
