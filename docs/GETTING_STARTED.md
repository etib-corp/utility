# Getting Started

This tutorial walks you from an empty project to using the Utility library. It
assumes you have already [built the library](../README.md#building).

## 1. Build the library

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## 2. Use a math type

Utility provides vectors, matrices, and quaternions under `utility::math`:

```cpp
#include <utility/math/vector.hpp>

utility::math::Vector3F a(1.0f, 2.0f, 3.0f);
utility::math::Vector3F b(4.0f, 5.0f, 6.0f);
auto sum = a + b;
auto dot = utility::math::dot(a, b);
```

## 3. Use a cache

`utility::Cache` provides a thread-safe key-value store:

```cpp
#include <utility/cache.hpp>

utility::Cache<std::string, int> cache;
cache.put("answer", 42);
auto value = cache.get("answer");  // std::optional<int>
```

## 4. Consume as a dependency

Once installed, link against `utility::utility`:

```cmake
find_package(utility CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE utility::utility)
```

## Next steps

- Read [How Utility Works](HOW_GUILLAUME_WORKS.md) for module details.
- Browse the [API reference](https://etib-corp.github.io/utility).
