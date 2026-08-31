# Benchmark harness for Utility.
#
# Built only when BUILD_BENCHMARKS=ON. Uses Google Benchmark to measure the key
# CPU hot paths: math (vector/matrix/quaternion), cache, and event dispatch.

include(FetchContent)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.1
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(utility_benchmarks
    benchmark_main.cpp
)

target_link_libraries(utility_benchmarks PRIVATE
    utility
    benchmark::benchmark
)

target_include_directories(utility_benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
