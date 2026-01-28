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

#include <stdexcept>
#include <utility>

#include "utility/logging/file_logger.hpp"

namespace utility::logging {

FileLogger::FileLogger(const std::string &filePath, bool append)
    : _filePath(filePath) {
  auto mode = append ? (std::ios::out | std::ios::app) : std::ios::out;
  _fileStream.open(_filePath, mode);

  if (!_fileStream.is_open()) {
    throw std::runtime_error("Failed to open log file: " + _filePath);
  }
}

FileLogger::FileLogger(const std::string &filePath, const std::string &name,
                       bool append)
    : _filePath(filePath) {
  setName(name);
  auto mode = append ? (std::ios::out | std::ios::app) : std::ios::out;
  _fileStream.open(_filePath, mode);

  if (!_fileStream.is_open()) {
    throw std::runtime_error("Failed to open log file: " + _filePath);
  }
}

FileLogger::~FileLogger() {
  if (_fileStream.is_open()) {
    _fileStream.flush();
    _fileStream.close();
  }
}

FileLogger::FileLogger(FileLogger &&other) noexcept
    : _fileStream(std::move(other._fileStream)),
      _filePath(std::move(other._filePath)) {}

FileLogger &FileLogger::operator=(FileLogger &&other) noexcept {
  if (this != &other) {
    if (_fileStream.is_open()) {
      _fileStream.close();
    }
    _fileStream = std::move(other._fileStream);
    _filePath = std::move(other._filePath);
  }
  return *this;
}

void FileLogger::debug(const std::string &message) {
  log(LogLevel::DEBUG, message);
}

void FileLogger::info(const std::string &message) {
  log(LogLevel::INFO, message);
}

void FileLogger::warning(const std::string &message) {
  log(LogLevel::WARNING, message);
}

void FileLogger::error(const std::string &message) {
  log(LogLevel::ERROR, message);
}

void FileLogger::log(LogLevel level, const std::string &message) {
  if (_fileStream.is_open()) {
    _fileStream << formatMessage(level, message) << std::endl;
    _fileStream.flush();
  }
}

const std::string &FileLogger::getFilePath() const { return _filePath; }

bool FileLogger::isOpen() const { return _fileStream.is_open(); }

} // namespace utility::logging
