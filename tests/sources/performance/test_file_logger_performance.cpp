#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>

#include "utility/logging/file_logger.hpp"

TEST(PerformanceFileLogger, OpenAndMetadataChecksCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  std::filesystem::create_directories("logs");

  constexpr std::uint32_t iterations = 5000;
  std::uint32_t openCount = 0;

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    std::string name = "perf_file_logger_" + std::to_string(i);
    utility::logging::FileLogger logger(name);
    if (logger.isOpen() && !logger.getFilePath().empty()) {
      ++openCount;
    }
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile std::uint32_t sink = openCount;
  (void)sink;

  RecordProperty("file_logger_open_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
