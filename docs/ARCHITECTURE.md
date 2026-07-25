# Utility Architecture

Utility is a shared foundation layer. Its namespaces are grouped by concern so
the rest of the workspace can reuse them without pulling in higher-level code.

## Main Areas

- `utility::math` contains vectors, matrices, quaternions, and scalar helpers.
- `utility::graphic` contains rendering-friendly types such as colors, poses,
  textures, vertices, and text helpers.
- `utility::event` contains platform and input event models.
- `utility::system_io` contains desktop and Android asset loading helpers.
- `utility::logging` contains logger interfaces and implementations.

## Design Goal

Keep the library small, reusable, and dependency-light so the engine, UI, and
application layers can share the same data model.
