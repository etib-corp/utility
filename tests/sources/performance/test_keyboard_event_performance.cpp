#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/event/keyboard_event.hpp"

TEST(PerformanceKeyboardEvent, StateUpdatesCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 200000;
  utility::event::KeyboardEvent event;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    event.setKeycode(utility::event::KeyboardEvent::KeyCode::RETURN);
    event.setIsDownEvent((i % 2U) == 0U);
    event.setIsRepeatEvent((i % 3U) == 0U);
    (void)event.getKeycode();
    (void)event.getIsDownEvent();
    (void)event.getIsRepeatEvent();
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile bool sink = event.getIsDownEvent();
  (void)sink;

  RecordProperty("keyboard_event_state_update_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
