# Utility Modules

This document describes each module's responsibilities, invariants, and
conventions. It is intended for adopters who need to integrate the library
into their own code.

## Conventions

### Namespaces and layout

Public headers live under `headers/utility/<module>/` and are included as
`utility/<module>/<header>.hpp`. Implementations live under `sources/` in the
same module structure.

### Coordinate systems

- Math primitives are engine-agnostic and use right-handed, Y-up conventions.
- `utility::graphic` types that are UI-facing (for example ray intersection
  helpers) may adopt a Y-down convention. Check the individual header for the
  intended convention before assuming a default.
- Angles are consistently expressed in **radians** throughout the library.
  Conversion helpers are available in `utility/math/trigonometric.hpp`.

### Numeric conventions

- Math components are floating-point (`float`/`double`). Matrices and vectors
  store components in **column-major** order for columns/rows of `2..4`, and
  `Matrix`/`Vector` provide both direct component access and GLM interop.
- Comparisons of floating-point types use the operators provided by the
  underlying GLM types; if you need tolerant comparisons, prefer an epsilon
  helper over `==`.

### Thread-safety

Thread-safety is opt-in per type. Unless a header explicitly documents
thread-safety, instances are **not** safe to share across threads without
external synchronization. Specifically:

- `utility::Cache` is declared thread-safe and is intended for concurrent
  access. (If you observe otherwise, report it: it must be synchronized.)
- `utility::logging` is currently not thread-safe; route logs from a single
  thread or add your own mutex.
- `utility::sound::AudioManager` uses a runtime control flag that must be
  treated as single-threaded access.

### Backend assumptions

- Graphics and font code assume a Vulkan-like depth range and Y-flip unless a
  header notes otherwise.
- Text rendering depends on FreeType; the public font APIs do not expose
  FreeType types directly, but they internally assume FreeType behavior.
- Audio depends on OpenAL Soft. Decoders are registered through
  `utility::sound::DecoderRegistry`.

## Modules

### `utility::math`

Vectors, matrices, quaternions, and scalar helpers backed by GLM.

- Types: `Vector`, `Matrix`, `Quaternion`, and free functions for perspective,
  look-at, rotation, and integer/trigonometric helpers.
- Invariants: square matrices default to a documented construction; component
  counts are fixed at compile time and validated at construction.
- Use: construct with braced lists of exactly the required number of
  components.

### `utility::graphic`

Rendering-friendly data types.

- Types: `Color`, `Pose`, `Position`, `Scale`, `Orientation`, `Vertex`,
  `Mesh`, `Material`, `Shader`, `Texture`, `View`, `Ray`, and text/font types
  (`Font`, `FontSized`, `CodePoints`, `Text`).
- Assets such as materials, models, shaders, and textures are usually loaded
  through `utility::RessourceProvider` rather than constructed directly.
- OBJ models are imported via tinyobjloader; images via stb.

### `utility::event`

Event models for input and XR interactions.

- Types: `Event`, `MouseMotionEvent`, `MouseButtonEvent`, keyboard and text
  input events, and XR hand events.
- Each concrete event exposes a `Factory` that produces either a base `Event`
  or a strongly typed instance.

### `utility::system_io`

Asset and file helpers for desktop and Android.

- `File` is an in-memory read/write buffer with a seek cursor. It stores
  content as a byte string; prefer it for in-memory asset manipulation.

### `utility::logging`

Logger interfaces and implementations.

- Provides a leveled logger. Levels control whether messages are emitted.

### `utility::sound`

Audio buffers, sources, and decoders.

- Types: `AudioBuffer`, `AudioSource`, `AudioManager`, and decoders for WAV
  and MP3 registered through `DecoderRegistry`.
