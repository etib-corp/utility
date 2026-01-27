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
 * @file logger.hpp
 * @brief Logging interface with levels and formatting utilities.
 *
 * Defines the `utility::Logger` abstract base class along with the `LogLevel`
 * enumeration. Implementations (e.g., `StandardLogger`, `FileLogger`) should
 * derive from `Logger` and provide concrete behavior for output.
 */

#pragma once

#include <string>

namespace utility {

/**
 * @brief Log severity levels.
 */
enum class LogLevel {
  DEBUG,   ///< Detailed debugging information
  INFO,    ///< General informational messages
  WARNING, ///< Warning messages for potentially harmful situations
  ERROR    ///< Error messages for serious problems
};

/**
 * @brief Abstract logger interface defining common logging operations.
 *
 * This interface provides a contract for all logger implementations,
 * supporting multiple log levels and formatted output.
 */
class Logger {
public:
  /**
   * @brief Virtual destructor for proper cleanup.
   */
  virtual ~Logger(void) = default;

  /**
   * @brief Log a debug message.
   * @param message The message to log.
   */
  virtual void debug(const std::string &message) = 0;

  /**
   * @brief Log an informational message.
   * @param message The message to log.
   */
  virtual void info(const std::string &message) = 0;

  /**
   * @brief Log a warning message.
   * @param message The message to log.
   */
  virtual void warning(const std::string &message) = 0;

  /**
   * @brief Log an error message.
   * @param message The message to log.
   */
  virtual void error(const std::string &message) = 0;

  /**
   * @brief Log a message with specified log level.
   * @param level The severity level.
   * @param message The message to log.
   */
  virtual void log(LogLevel level, const std::string &message) = 0;

  /**
   * @brief Set the logger name.
   * @param name The name to assign to this logger.
   */
  void setName(const std::string &name) { _name = name; }

  /**
   * @brief Get the logger name.
   * @return The name of this logger.
   */
  const std::string &getName(void) const { return _name; }

protected:
  /**
   * @brief Get string representation of log level.
   * @param level The log level to convert.
   * @return String representation of the level.
   */
  static std::string levelToString(LogLevel level);

  /**
   * @brief Get current timestamp as formatted string.
   * @return Formatted timestamp string.
   */
  static std::string getTimestamp(void);

  /**
   * @brief Format a log message with timestamp, logger name, and level.
   * @param level The log level.
   * @param message The message to format.
   * @return Formatted log message.
   */
  std::string formatMessage(LogLevel level, const std::string &message) const;

private:
  std::string _name; ///< Logger name
};

/**
 * @brief Concept to ensure a type inherits from Logger.
 * @tparam Type The type to check.
 */
template <typename Type>
concept InheritFromLogger = std::is_base_of_v<Logger, Type>;

} // namespace utility
