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

#include <string>
#include <exception>

class Error : public std::exception {
    public:
        /**
         * @enum ERROR_CELERITY
         * @brief Defines discrete error severity/urgency levels.
         *
         * This enum categorizes the relative importance or urgency of an error
         * condition. Values are assigned so the enumeration starts at 1 and
         * subsequent entries increment by one.
         *
         * Enumerators:
         *  - LOW (1):    Minor issues with little to no immediate impact.
         *  - MEDIUM (2): Issues that warrant attention but are not critical.
         *  - HIGH (3):   Critical issues that require immediate action.
         */
        enum class ERROR_CELERITY {
            LOW = 1,
            MEDIUM,
            HIGH
        };

        /**
         * @brief Create an Error with a descriptive message and an optional celerity level.
         *
         * @param message A human-readable description of the error. The message is copied into the
         *                Error object.
         * @param celerity An optional severity/urgency indicator for the error. Defaults to
         *                 ERROR_CELERITY::MEDIUM.
         *
         * The constructor is explicit to prevent implicit conversions from std::string to Error.
         * Note: copying the message can throw (e.g., std::bad_alloc) according to std::string's
         * exception guarantees.
         */
        explicit Error(const std::string &message, ERROR_CELERITY celerity = ERROR_CELERITY::MEDIUM)
            : _message(message), _celerity(celerity) {}

        virtual ~Error() noexcept = default;

        /**
         * @brief Returns a C-style string describing the error.
         *
         * Overrides std::exception::what(). The returned pointer refers to the
         * internal storage of the exception's std::string message and remains valid
         * as long as the exception object exists and its message is not modified.
         * This function is noexcept and safe to call when catching exceptions by
         * reference.
         *
         * @return const char* Null-terminated C-string containing the error message.
         */
        const char *what() const noexcept override {
            return _message.c_str();
        }

        /**
         * @brief Get the celerity value associated with this object.
         *
         * This accessor returns the stored ERROR_CELERITY value representing the
         * current celerity/state. It is a const member function and does not modify
         * the observable state of the object.
         *
         * @return ERROR_CELERITY The current celerity value.
         */
        ERROR_CELERITY get_celerity() const {
            return _celerity;
        }

    private:
        std::string _message;       ///< Descriptive error message
        ERROR_CELERITY _celerity;   ///< Error severity/urgency level
};
