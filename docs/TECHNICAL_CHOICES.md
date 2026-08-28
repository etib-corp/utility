# Utility Technical Choices

## Language

Utility is written in C++20 for consistency with the rest of the workspace.

## Dependencies

All dependencies are fetched at configure time with CMake `FetchContent` and
pinned to immutable tags or commit hashes so builds are reproducible.

- GLM for math primitives.
- tinyobjloader for mesh import support.
- stb for lightweight image and text asset support.
- FreeType for font and glyph handling.
- fmt for formatting.
- OpenAL Soft for audio output.
- dr_libs for audio decoding.
- DbgHelp on Windows for symbol and stack-related helpers.

## Build Model

Utility is built with CMake and exposes its headers as a reusable include
surface for the other libraries. It also ships install and export rules so it
can be consumed through `find_package(utility)`.

## Backend Assumptions

- Rendering and text code assume a Vulkan-like depth range and Y-flip unless a
  given header documents otherwise. UI-facing geometry may use a Y-down
  convention; verify per header.
- Text rendering internally depends on FreeType behavior.
- Audio depends on OpenAL Soft; codecs are resolved through the decoder
  registry.

## Design Choice

The library centralizes common support code so higher layers do not each grow
their own versions of the same helpers, while keeping module boundaries (and
their dependency rules) explicit.
