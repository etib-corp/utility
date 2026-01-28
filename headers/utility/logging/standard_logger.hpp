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

/**
 * @file standard_logger.hpp
 * @brief Standard output/error logger declaration.
 *
 * Declares `utility::StandardLogger`, which routes INFO/DEBUG to stdout and
 * WARNING/ERROR to stderr. See implementation in sources/standard_logger.cpp.
 */

#pragma once

#include "utility/logging/logger.hpp"

namespace utility::logging {

/**
 * @brief Standard output/error logger implementation.
 *
 * Logs DEBUG and INFO messages to stdout, WARNING and ERROR to stderr.
 */
class StandardLogger : public Logger {
public:
  /**
   * @brief Default constructor.
   */
  StandardLogger(void);

  /**
   * @brief Constructor with logger name.
   * @param name The name of the logger.
   */
  explicit StandardLogger(const std::string &name);

  /**
   * @brief Destructor ensuring output streams are flushed.
   */
  ~StandardLogger(void) override;

  /**
   * @brief Log a debug message to stdout.
   * @param message The message to log.
   */
  void debug(const std::string &message) override;

  /**
   * @brief Log an informational message to stdout.
   * @param message The message to log.
   */
  void info(const std::string &message) override;

  /**
   * @brief Log a warning message to stderr.
   * @param message The message to log.
   */
  void warning(const std::string &message) override;

  /**
   * @brief Log an error message to stderr.
   * @param message The message to log.
   */
  void error(const std::string &message) override;

  /**
   * @brief Log a message with specified level.
   *
   * Routes DEBUG and INFO to stdout, WARNING and ERROR to stderr.
   * @param level The severity level.
   * @param message The message to log.
   */
  void log(LogLevel level, const std::string &message) override;
};

} // namespace utility::logging
