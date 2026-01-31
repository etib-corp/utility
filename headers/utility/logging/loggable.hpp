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
 * @file loggable.hpp
 * @brief Mixin class to provide logging capabilities to derived classes.
 *
 * Defines the `utility::Loggable` base class that can be inherited by any class
 * that needs logging functionality. Derived classes gain access to logging
 * methods through an internal Logger instance.
 */

#pragma once

#include <memory>
#include <string>

#include "utility/logging/logger.hpp"

namespace utility::logging {

/**
 * @brief Mixin base class providing logging capabilities to derived classes.
 *
 * Any class that inherits from `Loggable` can use logging methods to output
 * debug, info, warning, and error messages. The logger is managed internally
 * and can be configured with a specific logger implementation.
 *
 * Example usage:
 * @code
 * class MyClass : public Loggable {
 * public:
 *   void doSomething() {
 *     log(LogLevel::INFO, "Doing something...");
 *   }
 * };
 *
 * StandardLogger logger("MyLogger");
 * MyClass obj;
 * obj.setLogger(&logger);
 * obj.doSomething(); // Outputs: [timestamp] [MyLogger] [INFO] Doing
 * something...
 * @endcode
 */
class Loggable {
public:
  /**
   * @brief Virtual destructor for proper cleanup in derived classes.
   */
  virtual ~Loggable(void) = default;

  /**
   * @brief Set the logger instance for this object.
   *
   * Assigns a logger that will be used for all logging operations in this
   * object. The logger must remain valid for the lifetime of this object.
   *
   * @param logger Pointer to a Logger instance. If nullptr, logging operations
   *               will be no-ops.
   */
  void setLogger(Logger *logger) { _logger = logger; }

  /**
   * @brief Get the current logger instance.
   *
   * @return Pointer to the current logger, or nullptr if no logger is set.
   */
  Logger *getLogger(void) const { return _logger; }

  /**
   * @brief Check if a logger is currently set.
   *
   * @return True if a logger is set and can be used, false otherwise.
   */
  bool hasLogger(void) const { return _logger != nullptr; }

protected:
  /**
   * @brief Default constructor.
   *
   * Initializes a Loggable object with no logger set. Call setLogger() to
   * assign a logger instance.
   */
  Loggable(void) = default;

  /**
   * @brief Constructor with logger.
   *
   * @param logger Pointer to a Logger instance to use for logging.
   */
  explicit Loggable(Logger *logger) : _logger(logger) {}

  /**
   * @brief Log a debug message.
   *
   * @param message The message to log.
   */
  void debug(const std::string &message) const {
    if (_logger) {
      _logger->debug(message);
    }
  }

  /**
   * @brief Log an informational message.
   *
   * @param message The message to log.
   */
  void info(const std::string &message) const {
    if (_logger) {
      _logger->info(message);
    }
  }

  /**
   * @brief Log a warning message.
   *
   * @param message The message to log.
   */
  void warning(const std::string &message) const {
    if (_logger) {
      _logger->warning(message);
    }
  }

  /**
   * @brief Log an error message.
   *
   * @param message The message to log.
   */
  void error(const std::string &message) const {
    if (_logger) {
      _logger->error(message);
    }
  }

  /**
   * @brief Log a message with specified level.
   *
   * @param level The severity level.
   * @param message The message to log.
   */
  void log(LogLevel level, const std::string &message) const {
    if (_logger) {
      _logger->log(level, message);
    }
  }

private:
  Logger *_logger = nullptr; ///< Pointer to the logger instance
};

} // namespace utility::logging
