#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/math/rectangle.hpp"

TEST(PerformanceRectangle, GeometryOperationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 200000;
  utility::math::Rectangle<float> rectangle(0.0F, 0.0F, 16.0F, 9.0F);
  utility::math::Rectangle<float> other(2.0F, 2.0F, 8.0F, 4.0F);

  std::uint32_t hits = 0;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    rectangle.translate(0.1F, -0.1F);
    if (rectangle.intersects(other) && rectangle.contains({rectangle.x(), rectangle.y()})) {
      ++hits;
    }
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile std::uint32_t sink = hits;
  (void)sink;

  RecordProperty("rectangle_geometry_ops_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
