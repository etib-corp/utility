#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/math/ray.hpp"

TEST(PerformanceRay, PointAndTranslationOperationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::math::Ray<float, 3> ray({0.0F, 0.0F, 0.0F}, {1.0F, -0.5F, 0.25F});

  utility::math::Vector<float, 3> accumulator{0.0F, 0.0F, 0.0F};

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    const auto t = static_cast<float>(i) * 0.001F;
    accumulator += ray.pointAt(t);
    ray.translate({0.001F, -0.001F, 0.0005F});
    (void)ray.normalizedDirection();
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile float sink = accumulator[0] + accumulator[1] + accumulator[2];
  (void)sink;

  RecordProperty("ray_point_translate_ops_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
