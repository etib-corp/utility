#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/singleton.hpp"

TEST(PerformanceSingleton, GetInstanceCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 300000;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    int &instance = utility::Singleton<int>::getInstance();
    instance = static_cast<int>(i);
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile int sink = utility::Singleton<int>::getInstance();
  (void)sink;

  RecordProperty("singleton_get_instance_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
