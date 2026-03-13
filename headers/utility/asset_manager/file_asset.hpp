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

#pragma once

#include <cstring>
#include <fstream>
#include <memory>
#include <string>

/**
 * @namespace utility
 * @brief The utility namespace contains classes and functions for the utility
 * project.
 */
namespace utility {
/**
 * @class FileAsset
 * @brief The FileAsset class represents a file asset in the evan project.
 *
 * This class provides methods to read and write binary data to and from a
 * file.
 */
class FileAsset {
public:
  /**
   * @enum Seek
   * @brief The Seek enum represents the different seek modes for file
   * operations.
   */
  enum class Seek {
    SET, ///> Seek from the beginning of the file
    CUR, ///> Seek from the current position in the file
    END  ///> Seek from the end of the file
  };

  /**
   * @brief Constructs a FileAsset object with its content and size.
   * @param content The content of the file.
   */
  FileAsset(const std::string &content);

  /**
   * @brief Destructs the FileAsset object.
   */
  ~FileAsset();

  /**
   * @brief Writes data to the file.
   * @param ptr The pointer to the data to write.
   * @param size The size of each element to write.
   * @param nmemb The number of elements to write.
   * @return The number of elements written.
   *
   * This method appends data at the seek position in the file.
   */
  size_t write(const void *ptr, size_t size, size_t nmemb);

  /**
   * @brief Reads data from the file.
   * @param ptr The pointer to the buffer to read data into.
   * @param size The size of each element to read.
   * @param count The number of elements to read.
   * @return The number of elements read.
   */
  size_t read(void *ptr, size_t size, size_t count);

  /**
   * @brief Reads data from the file.
   * @param str The string to read data into.
   * @param size The size of each element to read.
   * @param count The number of elements to read.
   * @return The number of elements read.
   */
  size_t read(std::string &str, size_t size, size_t count);

  /**
   * @brief Seeks to a specific position in the file.
   * @param offset The offset to seek to.
   * @param whence The seek mode (SET, CUR, END).
   * @return 0 on success, -1 on failure.
   */
  int seek(long offset, Seek whence);

  /**
   * @brief Returns the current position in the file.
   * @return The current position in the file.
   */
  size_t tell() const;

  /**
   * @brief Returns the content of the file.
   * @return The content of the file.
   * This method returns the content of the file as a string. The content is
   * stored in the _content member variable and can be accessed using this
   * method.
   */
  [[nodiscard]] inline const std::string &content() const {
    return _content;
  }

  /**
   * @brief Clears the content of the file.
   *
   * This method clears the content of the file by resetting the _content
   * member variable to an empty string and resetting the _pos member
   * variable to 0.
   * After calling this method, the file will be empty and the position will be
   * reset to the beginning of the file. This method can be used to clear the
   * content of the file before writing new data to it or to reset the file to
   * an empty state.
   */
  void clear();

  /**
   * @brief Removes a number of elements from the current position.
   * @param count The number of elements to remove.
   * @return The number of elements removed.
   */
  size_t remove(size_t count);

protected:
  /**
   * @brief In-memory content of the asset.
   */
  std::string _content;

  /**
   * @brief Current read/write cursor position in the content buffer.
   */
  size_t _pos = 0;
};
} // namespace utility
