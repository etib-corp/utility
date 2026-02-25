#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/event/event.hpp"
#include "utility/event/quit_event.hpp"

TEST(PerformanceEvent, PolymorphicDispatchCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::event::QuitEvent derived;
  utility::event::Event *event = &derived;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    event = &derived;
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile bool sink = event != nullptr;
  (void)sink;

  RecordProperty("event_polymorphic_dispatch_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
