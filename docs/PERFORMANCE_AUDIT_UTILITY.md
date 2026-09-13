# utility — Shared Types / Logging / RessourceProvider Performance Audit

## Role in the rendering architecture

```text
xider ──► guillaume ──► evan (Vulkan renderer)
                            └─► utility (RessourceProvider, logging, math, graphic types)
```

`utility` owns the lowest-level shared infrastructure:

- `RessourceProvider` — the CPU asset cache (fonts, meshes, models, textures,
  shaders, materials).
- The `Logger` hierarchy (`Logger`, `Loggable`, `StandardLogger`,
  `AndroidLogger`).
- `Mesh`/`Model`/`Text`/`ViewF` and the `graphic`/`math` types.

It has no GPU code, but two of its components are on the hot path and are root
causes of findings attributed to `evan` and `guillaume`:

1. **The always-on logger** — every hot-loop log call from `evan`/`guillaume`
   allocates an `std::ostringstream`, builds a `LogRecord`, takes a mutex, and
   flushes `std::cout`.
2. **`RessourceProvider` returning maps by value + `getShaderID` prefix scan** —
   every `evan::RessourceManager::sync()` pays map copies and O(M·E) scans.

---

## Executive summary

`utility` is small, but two of its APIs are force-multipliers for the
object-count-scaling costs found in `evan` and `guillaume`.

1. **CONFIRMED — `Logger::info/debug` is always active by default**
   (`_minLevel = DEBUG_LEVEL`). Each message lazily allocates an
   `std::ostringstream`, builds a `LogRecord` with a timestamp and copies
   strings, takes a mutex, and `StandardLogger::output` streams to
   `std::cout`/`std::cerr` with `std::endl` (flush).
2. **CONFIRMED — `RessourceProvider` accessors return resource maps by value**,
   and `getShaderID` scans `_elementsIDs` with `starts_with`, making every
   `RessourceManager::sync()` O(M·E) plus three map copies.

Fixing these two is low-risk and removes the constant factor behind the two
largest CPU findings elsewhere.

---

## Ranked findings

| Rank | Bottleneck | Confirmed? | Where |
| ---- | ---------- | ---------- | ----- |
| 1 | Logger always active; allocates + locks + flushes per message | CONFIRMED | `logger.hpp:84,110-116`; `standard_logger.cpp:70-97` |
| 2 | `RessourceProvider` returns maps by value | CONFIRMED | `RessourceProvider.hpp:77-105` |
| 3 | `getShaderID` prefix-scans `_elementsIDs` with `starts_with` | CONFIRMED | `ressource_provider.cpp:59-69` |
| 4 | `LogRecord` copies strings + timestamps per message | CONFIRMED | `logger.hpp`; `standard_logger.cpp` |

---

## Detailed analysis

### Logger (highest impact)

- `_minLevel = DEBUG_LEVEL` by default (`logger.hpp:84`), so `info`/`debug` are
  **always active**.
- Each message:
  1. lazily allocates an `std::ostringstream` (`logger.hpp:110-116`);
  2. builds a `LogRecord` with a timestamp and copies strings;
  3. takes a mutex;
  4. `StandardLogger::output` streams to `std::cout`/`std::cerr` **with
     `std::endl` (flush)** (`standard_logger.cpp:70-97`).

Because `evan` emits ~5 messages per mesh per eye and `guillaume` emits messages
per entity per system, this single component is the single largest
object-count-scaling CPU cost in the whole stack. See the `evan` and
`guillaume` audits for the call sites.

### RessourceProvider

- The resource accessors return `_shaders`, `_materials`, `_textures` maps **by
  value** (`RessourceProvider.hpp:77-105`). `evan::RessourceManager::sync()`
  copies all of them every frame and on every object add.
- `getShaderID(name)` scans `_elementsIDs` with `starts_with`
  (`ressource_provider.cpp:59-69`) — O(E) per material, making `sync()`
  O(M·E).

---

## Optimization roadmap

### P0 — Critical

| # | Problem | Evidence | Impact | CPU/GPU | Difficulty | Risk | Effort | Benchmark |
| - | ------- | -------- | ------ | ------- | ---------- | ---- | ------ | --------- |
| P0.1 (utility) | Logger always active; allocates/locks/flushes | `logger.hpp:84,110-116`; `standard_logger.cpp:70-97` | ~5 formatted+flushed lines per mesh per eye, and per entity per system | Very high, linear in N | CPU | Easy | Low | 0.5–1 day | Frame time with/without logs at N=100/1000 |
| P0.4 (utility) | `RessourceProvider` by-value maps + `getShaderID` prefix scan | `RessourceProvider.hpp:77-105`; `ressource_provider.cpp:59-69` | Map copies + O(M·E) scans every sync | High | CPU | Easy | Low | 1–2 days | `sync()` call count + time |

### Suggested fixes

- **Logger**: raise the default `_minLevel` (e.g. `INFO`/`WARNING` in release),
  add a cheap level pre-check before constructing the `ostringstream`, and make
  the flush policy configurable (buffered by default, flush on error).
- **RessourceProvider**: return maps by `const&`, cache the shader-ID lookup
  (or use an `unordered_map` keyed by name), and make `sync()` explicit /
  event-driven so it is not called from `recordCommandBuffer` or from
  `addMesh/addModel/addText`.

---

## Cross-references

- The draw-loop and per-entity logging call sites that invoke this logger live
  in `evan` and `guillaume` — see
  [`PERFORMANCE_AUDIT_EVAN.md`](PERFORMANCE_AUDIT_EVAN.md) and
  [`PERFORMANCE_AUDIT_GUILLAUME.md`](PERFORMANCE_AUDIT_GUILLAUME.md).
- `evan::RessourceManager` is the consumer of `RessourceProvider`'s by-value
  maps — see [`PERFORMANCE_AUDIT_EVAN.md`](PERFORMANCE_AUDIT_EVAN.md).
