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
 * @file default_logger.hpp
 * @brief Platform-specific default logger alias.
 *
 * On Android, `DefaultLogger` resolves to `AndroidLogger`.
 * On all other platforms, it resolves to `StandardLogger`.
 */

#pragma once

#ifdef __ANDROID__
	#include "utility/logging/android_logger.hpp"
namespace utility::logging
{
	/** @brief Alias for the platform-specific default logger. */
	using DefaultLogger = AndroidLogger;
}	 // namespace utility::logging
#else
	#include "utility/logging/standard_logger.hpp"
namespace utility::logging
{
	/** @brief Alias for the platform-specific default logger. */
	using DefaultLogger = StandardLogger;
}	 // namespace utility::logging
#endif
