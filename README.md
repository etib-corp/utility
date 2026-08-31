# Utility

Utility is the shared support library used by the other libraries in this
workspace. It collects common math, graphics, event, logging, asset, and helper
types so the higher layers can stay focused on UI and rendering.

It targets modern desktop and extended-reality (XR) applications and is written
in C++20.

## What It Provides

| Module | Headers | Purpose |
| ------ | ------- | ------- |
| `utility::math` | `headers/utility/math/` | Vectors, matrices, quaternions, trigonometric and integer helpers |
| `utility::graphic` | `headers/utility/graphic/` | Colors, poses, vertices, meshes, materials, shaders, text and font helpers |
| `utility::event` | `headers/utility/event/` | Mouse, keyboard, text-input, and XR hand event models |
| `utility::system_io` | `headers/utility/system_io/` | Desktop and Android asset / file loading helpers |
| `utility::logging` | `headers/utility/logging/` | Logger interfaces and implementations |
| `utility::sound` | `headers/utility/sound/` | Audio buffers, sources, and decoders |

## Requirements

- CMake 3.10 or newer
- A C++20 compiler
- Doxygen and Graphviz (only if you build the documentation)

Dependencies are fetched automatically at configure time using
`FetchContent`: GLM, tinyobjloader, stb, FreeType, fmt, OpenAL Soft, and
dr_libs.

## Building

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

To install the library so it can be consumed via `find_package`:

```sh
cmake --install build
```

The build is reproducible: all fetched dependencies are pinned to immutable
commit hashes or tags, never to moving branch names.

## Using in a downstream project

Once installed, link against the `utility::utility` target:

```cmake
find_package(utility CONFIG REQUIRED)

target_link_libraries(my_app PRIVATE utility::utility)
```

## Testing

Tests use GoogleTest and live under `tests/`. Enable them with
`-DBUILD_TESTING=ON`. They cover the math, graphic, event, system_io, logging,
and helper modules, including edge cases and invalid-input paths.

## Documentation

- [Architecture](docs/ARCHITECTURE.md)
- [Modules](docs/MODULES.md)
- [Getting Started](docs/GETTING_STARTED.md)
- [Versioning & Support](docs/VERSIONING.md)
- [Technical Choices](docs/TECHNICAL_CHOICES.md)
- [How Utility Works](docs/HOW_GUILLAUME_WORKS.md)
- [Code Conventions](docs/CODE_CONVENTIONS.md)
- [Commit Conventions](docs/COMMIT_CONVENTIONS.md)

## Contributing

We welcome contributions from the community! If you're interested in
contributing to Utility, please check out our
[Contributing Guidelines](CONTRIBUTING.md) for more information on how to get
involved.

## License

Utility is released under the [MIT License](LICENSE). See
[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for our community standards and
[SECURITY.md](SECURITY.md) for reporting vulnerabilities.
