/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace utility {
    /**
     * @brief Singleton class template.
     *
     * This class provides a thread-safe implementation of the singleton design pattern.
     * It ensures that only one instance of the class is created and provides global access to it.
     *
     * @tparam T The type of the singleton class.
     */
    template <typename T>
    class Singleton {
    public:
        // Delete copy constructor and assignment operator to prevent copying
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        /**
         * @brief Get the singleton instance.
         *
         * This method returns a shared pointer to the singleton instance.
         * If the instance does not exist, it is created.
         *
         * @return std::unique_ptr<T> A unique pointer to the singleton instance.
         */
        static T& getInstance() {
            static Singleton<T> singleton;
            if (!singleton._instance) {
                singleton._instance = std::make_unique<T>();
            }
            return singleton._instance;
        }
    private:
        // Private constructor to prevent direct instantiation
        Singleton() = default;

        T _instance;
    };
}