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
 * debug, info, warning, and error messages.
 */
template <InheritFromLogger LoggerType> class Loggable {
private:
  std::unique_ptr<LoggerType> _logger; ///< Internal logger instance

protected:
  /**
   * @brief Construct a Loggable with a default StandardLogger.
   */
  explicit Loggable(void)
      : _logger(std::make_unique<LoggerType>(typeid(*this).name())) {}

  /**
   * @brief Get the internal logger.
   * @return Reference to the internal Logger instance.
   */
  LoggerType &getLogger(void) { return *_logger; }

public:
  /**
   * @brief Virtual destructor for proper cleanup.
   */
  virtual ~Loggable(void) = default;
};

} // namespace utility::logging
