/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "performance/test_performance.hpp"

#include <chrono>
#include <cstdint>

TEST_F(TestPerformance, VectorArithmeticCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 200000;
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

TEST_F(TestPerformance, ColorOperationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 200000;
  utility::graphics::Color<float> colorA(0.2F, 0.4F, 0.6F, 0.8F);
  utility::graphics::Color<float> colorB(0.7F, 0.1F, 0.3F, 0.5F);

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
