# Changelog

All notable changes to this project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2026.1.0] - 2026-09-09

## [2026.1.1] - 2026-09-13

## [2026.1.2] - 2026-09-13

## [2026.1.3] - 2026-09-13

## [2026.1.4] - 2026-09-13

## [2026.1.5] - 2026-09-13

## [2026.1.6] - 2026-09-14

## [2026.1.7] - 2026-09-14

## [2026.1.8] - 2026-09-14

## [2026.1.9] - 2026-09-17

## [2026.1.10] - 2026-09-17

## [Unreleased]

### Added

- Standard open-source documentation: `CHANGELOG.md`, `CODE_OF_CONDUCT.md`,
  `CONTRIBUTING.md`, `SECURITY.md`, `AUTHORS.md`, and `LICENSE`.
- CPack packaging rules.
- Benchmark harness (`BUILD_BENCHMARKS`) covering math and cache hot paths.
- CI hardening: ASan/UBSan and `clang-tidy` jobs, and coverage reporting.
- Documentation: Getting Started tutorial, architecture diagrams, and
  versioning & support policy.
- A runnable `examples/math_vectors` sample.
- Logging: `FlushPolicy` enum (`BUFFERED`, `ALWAYS`, `NEVER`) with
  `Logger::setFlushPolicy()` / `getFlushPolicy()`, and a
  `Logger::defaultMinLevel()` helper.
- Logging benchmarks comparing suppressed vs. active emission at N=100/1000.
- `RessourceProvider::version()`, a monotonic counter bumped on every mutation
  of the provider's resource maps (new ids and in-place content updates such
  as font atlases), letting consumers skip their work while it is unchanged.
- Math: `utility::math::Aabb` — a 3D axis-aligned bounding box template with
  `AabbF`/`AabbD` aliases, construction from point ranges (`fromPoints`),
  growth via `include()`, and queries (`center`, `extents`, `halfSize`,
  `radius`, `positiveVertex`, `contains`, `intersects`, `isEmpty`) for frustum
  and distance culling.
- Graphics: `utility::graphic::transform.hpp` with `poseToMatrix()`,
  `orientationToMatrix()` and `modelMatrix(pose, scale)` helpers, plus
  `Renderable::getModelMatrix()`, to convert a `PoseF`/`ScaleF` into the
  `glm::mat4` model matrix expected by per-instance rendering.
- Graphics: `utility::graphic::AlphaMode` (`Opaque`, `Mask`, `Blend`) with
  `Material::getAlphaMode()` and `Material::getAlphaCutoff()`, giving materials
  an authoritative source of truth for alpha semantics. Materials default to
  `Opaque` with a `0.5` cutoff (the glTF defaults); `TextMaterial` is `Blend`,
  so consumers no longer have to infer transparency from texture types or
  shader names.

### Changed

- **Behaviour change (breaking):** meshes are now stored in local (object)
  space. `Model::loadOBJ` no longer bakes the pose position into vertex
  positions, and `Text::updateMesh` no longer bakes the pose position or
  orientation into its glyph quads. Callers must apply the world transform
  through the model matrix (`Renderable::getModelMatrix()` or
  `poseToMatrix()`) instead of relying on pre-transformed vertices. This
  matches `evan`'s per-instance model matrix (instance attribute locations
  3..6).
- Replaced `file(GLOB)` with explicit source lists for reproducible builds.
- Logging: the default minimum level is now `WARNING_LEVEL` in release builds
  (`NDEBUG`) and `DEBUG_LEVEL` in debug builds, instead of always
  `DEBUG_LEVEL`. Hot-loop `debug`/`info` calls are therefore suppressed in
  release; set `UTILITY_LOG_LEVEL` (`debug`, `info`, `warning`, `error`) or
  call `Logger::setMinLevel()` to restore verbosity.
- Logging: `StandardLogger` no longer flushes on every line. Output is
  buffered (`'\n'`) by default and flushed for warnings/errors and on
  destruction; `setFlushPolicy(FlushPolicy::ALWAYS)` restores the previous
  per-line `std::endl` behavior.
- Logging: `Logger::_minLevel` is now a `std::atomic<LogLevel>`; level reads
  and writes are lock-free, and a suppressed message performs no allocation
  and takes no mutex. `Logger::levelValue()` is `constexpr`/inline.
- **API change (breaking):** `RessourceProvider` resource accessors
  (`getMaterials`, `getTextures`, `getModels`, `getShaders`,
  `getCodePoints`) now return their internal maps by `const&` instead of by
  value, removing a full container copy (and one `shared_ptr` refcount bump
  per element) on every access. The returned reference is valid only until
  the next mutating call (any `load*` method) on the provider.
- **Performance:** logging no longer performs several heap allocations per
  emitted line. `LogMessage` moves the stream buffer into
  `LogRecord::message` instead of copying it, `Logger::getTimestamp()`
  formats into a stack buffer instead of a `std::stringstream`, and
  `StandardLogger::output()` writes directly to the destination stream
  without building an intermediate `std::stringstream`. The emitted line
  format is unchanged.
- `RessourceProvider` font-atlas handling is centralized in the new
  `onFontAtlasCreated()` helper instead of being duplicated in
  `loadFontFromAsset()` and `loadFontFamilyFromAssets()`; the shared
  implementation records the in-place material update with `touch()`.

### Fixed

- `RessourceProvider::getShaderID()` no longer scans `_elementsIDs`, which made
  `evan::RessourceManager::sync()` O(M·E). Shaders are now resolved through a
  dedicated, shader-only index (`_shaderIDs`), giving O(1) average lookups.
  Ambiguous prefixes resolve deterministically to the first-registered shader
  (lowest id) instead of following an unspecified `unordered_map` iteration
  order; unknown names still return `0`.

## [1.0.0] - 2025-08-25

### Added

- Initial release of the Utility shared support library.
- `utility::math` module with vectors, matrices, quaternions, and scalar helpers.
- `utility::graphic` module with colors, poses, vertices, meshes, materials,
  shaders, text, and font helpers.
- `utility::event` module with mouse, keyboard, text-input, and XR hand events.
- `utility::system_io` module with desktop and Android asset / file loading.
- `utility::logging` module with logger interfaces and implementations.
- `utility::sound` module with audio buffers, sources, and decoders.
