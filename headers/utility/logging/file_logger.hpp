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
 * @file file_logger.hpp
 * @brief File-based logger declaration.
 *
 * Declares `utility::FileLogger`, which writes all log messages to a file
 * with optional append mode and flushes after each entry. Implementation in
 * sources/file_logger.cpp.
 */

#pragma once


#include <fstream>
#include <string>

#include "utility/logging/logger.hpp"

namespace utility::logging {

/**
 * @brief File-based logger implementation.
 *
 * Logs all messages to a specified file with automatic flushing.
 */
class FileLogger : public Logger {
private:
  std::ofstream _fileStream; ///< Output file stream
  std::string _filePath;     ///< Path to the log file

public:
  /**
   * @brief Construct a file logger.
   * @param filePath Path to the log file.
   * @param append If true, append to existing file; otherwise truncate.
   * @throws std::runtime_error if file cannot be opened.
   */
  explicit FileLogger(const std::string &filePath, bool append = true);

  /**
   * @brief Construct a file logger with a name.
   * @param filePath Path to the log file.
   * @param name The name of the logger.
   * @param append If true, append to existing file; otherwise truncate.
   * @throws std::runtime_error if file cannot be opened.
   */
  FileLogger(const std::string &filePath, const std::string &name,
             bool append = true);

  /**
   * @brief Destructor ensuring file is properly closed.
   */
  ~FileLogger(void) override;

  /**
   * @brief Disable copy construction and assignment.
   * @param other The FileLogger to copy from.
   */
  FileLogger(const FileLogger &other) = delete;

  /**
   * @brief Disable copy assignment.
   * @return Reference to this FileLogger.
   */
  FileLogger &operator=(const FileLogger &other) = delete;

  /**
   * @brief Move constructor.
   * @param other The FileLogger to move from.
   */
  FileLogger(FileLogger &&other) noexcept;

  /**
   * @brief Move assignment operator.
   * @param other The FileLogger to move from.
   * @return Reference to this FileLogger.
   */
  FileLogger &operator=(FileLogger &&other) noexcept;

  /**
   * @brief Log a debug message to file.
   * @param message The message to log.
   */
  void debug(const std::string &message) override;

  /**
   * @brief Log an informational message to file.
   * @param message The message to log.
   */
  void info(const std::string &message) override;

  /**
   * @brief Log a warning message to file.
   * @param message The message to log.
   */
  void warning(const std::string &message) override;

  /**
   * @brief Log an error message to file.
   * @param message The message to log.
   */
  void error(const std::string &message) override;

  /**
   * @brief Log a message with specified level to file.
   * @param level The severity level.
   * @param message The message to log.
   */
  void log(LogLevel level, const std::string &message) override;

  /**
   * @brief Get the path to the log file.
   * @return The log file path.
   */
  const std::string &getFilePath() const;

  /**
   * @brief Check if the log file is currently open.
   * @return True if file is open, false otherwise.
   */
  bool isOpen(void) const;
};

} // namespace utility::logging
