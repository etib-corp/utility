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

#include "logging/test_loggable.hpp"

#include <iostream>
#include <sstream>

#include "utility/logging/standard_logger.hpp"

namespace {

class LoggableFixture
    : public utility::logging::Loggable<LoggableFixture,
                                        utility::logging::StandardLogger> {
public:
  void writeInfo(const std::string &message) { getLogger().info(message); }
};

} // namespace

TEST_F(TestLoggable, ProvidesUsableLoggerFromMixin) {
  std::stringstream capturedStdout;
  std::streambuf *oldStdout = std::cout.rdbuf(capturedStdout.rdbuf());

  LoggableFixture fixture;
  fixture.writeInfo("loggable payload");

  std::cout.rdbuf(oldStdout);
  const std::string output = capturedStdout.str();

  EXPECT_NE(output.find("[INFO_LEVEL]"), std::string::npos);
  EXPECT_NE(output.find("loggable payload"), std::string::npos);
}