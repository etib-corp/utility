# Utility Architecture

Utility is a shared foundation layer. Its namespaces are grouped by concern so
the rest of the workspace can reuse them without pulling in higher-level code.

## Main Areas

- `utility::math` contains vectors, matrices, quaternions, and scalar helpers.
- `utility::graphic` contains rendering-friendly types such as colors, poses,
  textures, vertices, and text helpers.
- `utility::event` contains platform and input event models.
- `utility::system_io` contains desktop and Android asset loading helpers.
- `utility::sound` contains audio buffers, sources, and decoders.
- `utility::logging` contains logger interfaces and implementations.

## Layer Ownership

Utility sits at the bottom of the dependency stack. Higher layers (engine, UI,
application) depend on Utility; Utility must never depend on them.

```
 Application
     |
   UI / Rendering
     |
   Engine
     |
 Utility  <- shared foundation
```

Because every layer shares the same data model, care must be taken to keep
module boundaries clean:

- `utility::math` has no dependencies on other utility modules.
- `utility::graphic` may depend on `utility::math` and `utility::system_io`.
- `utility::system_io` should not depend on graphic or logging types.
- `utility::event` depends only on `utility::math`.

## Dependency Flow

Dependencies are fetched with CMake `FetchContent` and pinned to immutable
tags or commit hashes for reproducible builds. See
[TECHNICAL_CHOICES.md](TECHNICAL_CHOICES.md) for the full list.

## Build and Package

- The project builds a static/shared `utility` target and exports
  `utility::utility` for downstream `find_package` consumers.
- Tests are optional (`BUILD_TESTING=ON`) and use GoogleTest.
- Documentation is optional (`BUILD_DOCS=ON`) and built with Doxygen.

See [MODULES.md](MODULES.md) for per-module invariants, coordinate and
thread-safety conventions.
