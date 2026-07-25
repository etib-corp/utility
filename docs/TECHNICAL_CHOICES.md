# Utility Technical Choices

## Language

Utility is written in C++20 for consistency with the rest of the workspace.

## Dependencies

- GLM for math primitives.
- tinyobjloader for mesh import support.
- stb for lightweight image and text asset support.
- freetype for font and glyph handling.
- DbgHelp on Windows for symbol and stack-related helpers.

## Build Model

Utility is built with CMake and exposes its headers as a reusable include
surface for the other libraries.

## Design Choice

The library centralizes common support code so higher layers do not each grow
their own versions of the same helpers.
