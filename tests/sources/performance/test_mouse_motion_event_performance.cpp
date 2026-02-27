#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/event/mouse_motion_event.hpp"

TEST(PerformanceMouseMotionEvent, PositionUpdatesCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::event::MouseMotionEvent event;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    event.setPosition(
        {static_cast<float>(i % 1024U), static_cast<float>(i % 768U)});
    (void)event.getPosition();
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  const auto position = event.getPosition();
  volatile float sink = position[0] + position[1];
  (void)sink;

  RecordProperty("mouse_motion_event_ops_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
