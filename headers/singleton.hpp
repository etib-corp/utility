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

#include <concepts>

namespace utility {

/**
 * @brief Concept to ensure the class can be a singleton.
 * @tparam Type The type to check.
 */
template <typename Type>
concept CanBeSingleton =
    std::default_initializable<Type> && std::destructible<Type>;

/**
 * @brief Singleton class template.
 *
 * This class provides a thread-safe implementation of the singleton design
 * pattern. It ensures that only one instance of the class is created and
 * provides global access to it.
 *
 * @tparam Type The type of the singleton class.
 */
template <CanBeSingleton Type> class Singleton {
public:
  // Delete copy constructor and assignment operator to prevent copying
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  /**
   * @brief Get the singleton instance.
   *
   * This method returns a shared pointer to the singleton instance.
   * If the instance does not exist, it is created.
   *
   * @return A reference to the singleton instance.
   */
  static Type &getInstance(void) {
    static Singleton<Type> singleton;
    if (!singleton._instance) {
      singleton._instance = Type();
    }
    return singleton._instance;
  }

private:
  // Private constructor to prevent direct instantiation
  Singleton(void) = default;

  Type _instance; ///< The singleton instance.
};

/**
 * @brief Concept to ensure a Singleton type is provided.
 * @tparam Type The type to check.
 */
template <typename Type>
concept IsSingletonOf = requires {
  { Type::getInstance() } -> std::same_as<Type &>;
};

} // namespace utility
