#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>
#include <string>

#include "utility/logging/logger.hpp"

namespace {

class PerformanceTestLogger : public utility::logging::Logger {
public:
  explicit PerformanceTestLogger(std::string &name)
      : utility::logging::Logger(name) {}

  std::string exposeFormatMessage(utility::logging::LogLevel level,
                                  const std::string &message) const {
    return formatMessage(level, message);
  }

  void debug(const std::string &) override {}
  void info(const std::string &) override {}
  void warning(const std::string &) override {}
  void error(const std::string &) override {}
  void log(utility::logging::LogLevel, const std::string &) override {}
};

} // namespace

TEST(PerformanceLogger, MessageFormattingCompletesWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 120000;
  std::string name = "perf_logger";
  PerformanceTestLogger logger(name);
  std::string last;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    last = logger.exposeFormatMessage(utility::logging::LogLevel::INFO_LEVEL,
                                      "payload_" + std::to_string(i));
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile std::size_t sink = last.size();
  (void)sink;

  RecordProperty("logger_format_message_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
