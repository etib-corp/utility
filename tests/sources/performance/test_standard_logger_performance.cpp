#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>
#include <string>

#include "utility/logging/standard_logger.hpp"

TEST(PerformanceStandardLogger, ConstructionCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 70000;
  std::uint32_t count = 0;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    std::string name = "std_logger_perf_" + std::to_string(i);
    utility::logging::StandardLogger logger(name);
    if (!name.empty()) {
      ++count;
    }
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile std::uint32_t sink = count;
  (void)sink;

  RecordProperty("standard_logger_construction_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
