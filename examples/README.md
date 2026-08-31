# Utility Examples

This directory contains runnable samples that demonstrate how to use the
Utility library.

## math_vectors

A minimal sample that demonstrates the `utility::math` vector API (addition,
dot product, and normalization). It is CPU-only and runs anywhere.

### Building

```sh
cmake -S . -B build -DBUILD_EXAMPLES=ON
cmake --build build --target utility_math_vectors
```

### Running

```sh
./build/examples/math_vectors/utility_math_vectors
```
