# Utility Examples

This directory contains runnable samples that demonstrate how to use the
Utility library.

The examples are CPU-only and can be built together with:

```sh
cmake -S . -B build -DBUILD_EXAMPLES=ON
cmake --build build --target utility_cache utility_graphic_colors \\
	utility_math_matrices utility_sound_mp3 utility_math_vectors
```

Run the executables from `build/examples/<example>/`.

## cache

Demonstrates inserting, retrieving, checking, and removing entries from the
thread-safe `utility::Cache`.

## graphic_colors

Demonstrates alpha blending and grayscale conversion with
`utility::graphic::ColorFloat`.

## math_matrices

Demonstrates determinant and inverse operations with `utility::math` matrices.

## sound_mp3

Decodes and plays an MP3 through the OpenAL-backed sound API for five seconds
by default. The repository does not include an audio asset; provide your own
MP3 file when running the example:

```sh
./build/examples/sound_mp3/utility_sound_mp3 /path/to/audio.mp3
./build/examples/sound_mp3/utility_sound_mp3 /path/to/audio.mp3 10
```

The host must have an available OpenAL playback device.

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
