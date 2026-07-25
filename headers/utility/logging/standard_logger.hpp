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
 * @file standard_logger.hpp
 * @brief Standard output/error logger declaration.
 *
 * Declares `utility::StandardLogger`, which routes INFO_LEVEL/DEBUG_LEVEL to
 * stdout and WARNING_LEVEL/ERROR_LEVEL to stderr, with ANSI colors and
 * enriched metadata.
 */

#pragma once

#include "utility/logging/logger.hpp"

namespace utility::logging
{

	/**
	 * @brief Standard output/error logger implementation.
	 *
	 * Logs DEBUG_LEVEL and INFO_LEVEL messages to stdout, WARNING_LEVEL and
	 * ERROR_LEVEL to stderr. Adds ANSI color per level and includes source
	 * file, line, and function name in the output only for DEBUG_LEVEL.
	 */
	class StandardLogger: public Logger
	{
		public:
		/**
		 * @brief Constructor with logger name.
		 * @param name The name of the logger.
		 */
		StandardLogger(const std::string &name);

		/**
		 * @brief Destructor ensuring output streams are flushed.
		 */
		~StandardLogger(void) override;

		/**
		 * @brief Output a formatted log record to the appropriate stream.
		 * @param record The log record to output.
		 */
		void output(const LogRecord &record) override;
	};

}	 // namespace utility::logging
