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

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "utility/logging/standard_logger.hpp"

namespace utility::logging
{

	StandardLogger::StandardLogger(const std::string &name)
		: Logger(name)
	{
	}

	StandardLogger::~StandardLogger()
	{
		std::cout.flush();
		std::cerr.flush();
	}

	static bool useColor()
	{
		const char *noColor = std::getenv("NO_COLOR");
		return noColor == nullptr || noColor[0] == '\0';
	}

	static const char *levelColor(LogLevel level)
	{
		switch (level) {
			case LogLevel::DEBUG_LEVEL:
				return "\033[36m";
			case LogLevel::INFO_LEVEL:
				return "\033[32m";
			case LogLevel::WARNING_LEVEL:
				return "\033[33m";
			case LogLevel::ERROR_LEVEL:
				return "\033[31m";
			default:
				return "\033[0m";
		}
	}

	static const char *resetColor()
	{
		return "\033[0m";
	}

	void StandardLogger::output(const LogRecord &record)
	{
		std::stringstream ss;
		ss << "[" << record.timestamp << "] ";
		ss << "[" << record.loggerName << "] ";

		bool color = useColor();
		if (color) {
			ss << levelColor(record.level);
		}
		ss << "[" << levelToString(record.level) << "] ";
		if (color) {
			ss << resetColor();
		}

		if (record.level == LogLevel::DEBUG_LEVEL) {
			ss << "[" << record.file << ":" << record.line << " "
			   << record.function << "] ";
		}
		ss << record.message;

		if (record.level == LogLevel::WARNING_LEVEL
			|| record.level == LogLevel::ERROR_LEVEL) {
			std::cerr << ss.str() << std::endl;
		} else {
			std::cout << ss.str() << std::endl;
		}
	}

}	 // namespace utility::logging
