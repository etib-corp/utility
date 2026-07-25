# Utility

Utility is the shared support library used by the other libraries in this
workspace. It collects common math, graphics, event, logging, asset, and helper
types so the higher layers can stay focused on UI and rendering.

## What It Provides

- Math primitives and helpers.
- Graphics data types such as vertices, colors, poses, and meshes.
- Event models for mouse, keyboard, text input, and XR hand interactions.
- Logging and singleton helpers.
- Asset manager abstractions for desktop and Android.

## Build Notes

Utility is a C++20 library built with CMake and fetched dependencies such as
GLM, tinyobjloader, stb, and freetype.

## Documentation

- [Architecture](docs/ARCHITECTURE.md)
- [How Utility Works](docs/HOW_GUILLAUME_WORKS.md)
- [Technical Choices](docs/TECHNICAL_CHOICES.md)
