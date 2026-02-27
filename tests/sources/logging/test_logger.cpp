/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "logging/test_logger.hpp"
namespace {

class TestableLogger : public utility::logging::Logger {
public:
  explicit TestableLogger(std::string &name) : utility::logging::Logger(name) {}

  static std::string exposeLevelToString(utility::logging::LogLevel level) {
    return levelToString(level);
  }

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

TEST_F(TestLogger, LevelToStringMapsKnownValues) {
  EXPECT_EQ(
      TestableLogger::exposeLevelToString(utility::logging::LogLevel::DEBUG),
      "DEBUG");
  EXPECT_EQ(
      TestableLogger::exposeLevelToString(utility::logging::LogLevel::INFO),
      "INFO");
  EXPECT_EQ(
      TestableLogger::exposeLevelToString(utility::logging::LogLevel::WARNING),
      "WARNING");
  EXPECT_EQ(
      TestableLogger::exposeLevelToString(utility::logging::LogLevel::ERROR),
      "ERROR");
}

TEST_F(TestLogger, FormatMessageIncludesNameLevelAndPayload) {
  std::string name = "unit_logger";
  const TestableLogger logger(name);

  const std::string formatted =
      logger.exposeFormatMessage(utility::logging::LogLevel::INFO, "hello");

  EXPECT_NE(formatted.find("[unit_logger]"), std::string::npos);
  EXPECT_NE(formatted.find("[INFO]"), std::string::npos);
  EXPECT_NE(formatted.find("hello"), std::string::npos);
}