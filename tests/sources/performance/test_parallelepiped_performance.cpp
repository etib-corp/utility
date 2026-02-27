#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/math/parallelepiped.hpp"

TEST(PerformanceParallelepiped, SetGetOperationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::math::Parallelepiped<float> shape;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    const utility::math::Vector<float, 3> position{static_cast<float>(i % 100U),
                                                   static_cast<float>(i % 50U),
                                                   static_cast<float>(i % 25U)};
    const utility::math::Vector<float, 3> origin{0.5F, 0.5F, 0.5F};
    const utility::math::Vector<float, 3> size{10.0F, 20.0F, 30.0F};

    shape.setPosition(position);
    shape.setOrigin(origin);
    shape.setSize(size);
    (void)shape.getPosition();
    (void)shape.getOrigin();
    (void)shape.getSize();
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  const auto position = shape.getPosition();
  volatile float sink = position[0] + position[1] + position[2];
  (void)sink;

  RecordProperty("parallelepiped_set_get_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
