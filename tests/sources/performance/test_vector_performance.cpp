#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/math/vector.hpp"

TEST(PerformanceVector, ArithmeticCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::math::Vector<float, 3> accumulator{0.0F, 0.0F, 0.0F};
  utility::math::Vector<float, 3> direction{1.0F, -2.0F, 3.0F};

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    accumulator += direction;
    accumulator -= direction * 0.5F;
    accumulator = accumulator + direction / 2.0F;
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile float sink = accumulator[0] + accumulator[1] + accumulator[2];
  (void)sink;

  RecordProperty("vector_arithmetic_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
