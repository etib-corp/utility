#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/logging/loggable.hpp"
#include "utility/logging/standard_logger.hpp"

namespace {

class PerformanceLoggableFixture
    : public utility::logging::Loggable<PerformanceLoggableFixture,
                                        utility::logging::StandardLogger> {
public:
  utility::logging::StandardLogger &exposeLogger(void) { return getLogger(); }
};

} // namespace

TEST(PerformanceLoggable, LoggerAccessCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 300000;
  PerformanceLoggableFixture fixture;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    auto &logger = fixture.exposeLogger();
    (void)logger;
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  RecordProperty("loggable_logger_access_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
