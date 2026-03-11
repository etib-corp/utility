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

#include "logging/test_standard_logger.hpp"

#include <iostream>
#include <sstream>

TEST_F(TestStandardLogger, InfoAndDebugGoToStdout) {
  std::stringstream capturedStdout;
  std::streambuf *oldStdout = std::cout.rdbuf(capturedStdout.rdbuf());

  std::string name = "std_logger";
  utility::logging::StandardLogger logger(name);
  logger.debug("debug message");
  logger.info("info message");

  std::cout.rdbuf(oldStdout);

  const std::string output = capturedStdout.str();
  EXPECT_NE(output.find("[DEBUG_LEVEL]"), std::string::npos);
  EXPECT_NE(output.find("debug message"), std::string::npos);
  EXPECT_NE(output.find("[INFO_LEVEL]"), std::string::npos);
  EXPECT_NE(output.find("info message"), std::string::npos);
}

TEST_F(TestStandardLogger, WarningAndErrorGoToStderr) {
  std::stringstream capturedStderr;
  std::streambuf *oldStderr = std::cerr.rdbuf(capturedStderr.rdbuf());

  std::string name = "std_logger";
  utility::logging::StandardLogger logger(name);
  logger.warning("warning message");
  logger.error("error message");

  std::cerr.rdbuf(oldStderr);

  const std::string output = capturedStderr.str();
  EXPECT_NE(output.find("[WARNING_LEVEL]"), std::string::npos);
  EXPECT_NE(output.find("warning message"), std::string::npos);
  EXPECT_NE(output.find("[ERROR_LEVEL]"), std::string::npos);
  EXPECT_NE(output.find("error message"), std::string::npos);
}
