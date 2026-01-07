# Utility

**A comprehensive C++ utilities library tailored for the development of modern desktop and extended reality (XR) applications.**

## Key Features

## Quick Start

```cpp
```

## Documentation

- **[How Utility Works](docs/HOW_UTILITY_WORKS.md)** - Comprehensive guide to concepts, lifecycle, and usage patterns
- **[Architecture Documentation](docs/ARCHITECTURE.md)** - Detailed overview of the system's design and components
- **[Technical Choices Documentation](docs/TECHNICAL_CHOICES.md)** - Insights into design decisions and technologies

## Building

Utility builds as a static library along with examples and tests:

1. Clone the repository:

```bash
git clone https://github.com/etib-corp/utility.git
cd utility
```

1. Configure and build using CMake:

```bash
cmake -S . -B build
cmake --build build
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
