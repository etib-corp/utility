# Utility

Utility is a C++ library built to streamline the development of interactive libraries and applications. It offers classes for creating seamless interfaces between libraries and programs, managing primitives and events tailored for XR environments.

## Key Features

- **Rendering Primitives**: Classes for 2D and 3D shapes, text rendering, and image handling.

- **Event Handling**: Mechanisms to capture and respond to user inputs such as keyboard and mouse events.

## Building

Utility builds as a static library along with examples and tests:

```bash
cmake -S . -B build
cmake --build build
```

### Running Examples

After building, you can run the examples:

```bash
# Basic Demo (comprehensive)
./examples/basic_demo/basic_demo
```

### Running Tests

To run the test suite:

```bash
./tests/test_utility
```

### Using Utility in Your Project

Utility builds as a static library (`libutility.a`) with minimal dependencies. To use it in your CMake project:

```cmake
# Link with Utility (core library has no external dependencies)
target_link_libraries(your_target PRIVATE utility)
```

## Examples

The `examples/` directory contains sample applications demonstrating Utility's features. Each example is organized in its own subdirectory:

- **basic_demo/**: Comprehensive example showing various features of the Utility library.
