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

### Changed

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
