#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/math/color.hpp"

TEST(PerformanceColor, TransformationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::math::Color<float> colorA(0.2F, 0.4F, 0.6F, 0.8F);
  utility::math::Color<float> colorB(0.7F, 0.1F, 0.3F, 0.5F);

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    colorA = colorA.blendOver(colorB).grayscale().lighter(0.1F).darker(0.05F);
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile float sink = colorA.red() + colorA.green() + colorA.blue();
  (void)sink;

  RecordProperty("color_operations_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
