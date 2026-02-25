#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/event/mouse_button_event.hpp"

TEST(PerformanceMouseButtonEvent, PositionAndButtonsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 200000;
  utility::event::MouseButtonEvent event;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    event.setPosition({static_cast<float>(i % 500U), static_cast<float>(i % 300U)});
    event.setButtonState(utility::event::MouseButtonEvent::MouseButton::LEFT,
                         (i % 2U) == 0U);
    (void)event.getPosition();
    (void)event.isButtonPressed(
        utility::event::MouseButtonEvent::MouseButton::LEFT);
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile bool sink = event.isButtonPressed(
      utility::event::MouseButtonEvent::MouseButton::LEFT);
  (void)sink;

  RecordProperty("mouse_button_event_ops_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
