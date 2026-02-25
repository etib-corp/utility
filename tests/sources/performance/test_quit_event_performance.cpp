#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/event/quit_event.hpp"

TEST(PerformanceQuitEvent, ConstructionCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 300000;
  std::uint32_t count = 0;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    utility::event::QuitEvent event;
    count += static_cast<std::uint32_t>(sizeof(event) > 0U);
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile std::uint32_t sink = count;
  (void)sink;

  RecordProperty("quit_event_construction_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
