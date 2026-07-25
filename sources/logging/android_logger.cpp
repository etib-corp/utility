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

#include "utility/logging/android_logger.hpp"

#ifdef __ANDROID__

namespace utility::logging
{

	AndroidLogger::AndroidLogger(const std::string &name)
		: Logger(name)
	{
	}

	AndroidLogger::~AndroidLogger() = default;

	void AndroidLogger::output(const LogRecord &record)
	{
		android_LogPriority priority = ANDROID_LOG_VERBOSE;
		switch (record.level) {
			case LogLevel::DEBUG_LEVEL:
				priority = ANDROID_LOG_DEBUG;
				break;
			case LogLevel::INFO_LEVEL:
				priority = ANDROID_LOG_INFO;
				break;
			case LogLevel::WARNING_LEVEL:
				priority = ANDROID_LOG_WARN;
				break;
			case LogLevel::ERROR_LEVEL:
				priority = ANDROID_LOG_ERROR;
				break;
		}

		std::string tag = record.loggerName;
		std::string msg = "[" + record.timestamp + "] ";
		if (record.level == LogLevel::DEBUG_LEVEL) {
			msg += "[" + record.file + ":" + std::to_string(record.line) + " "
				+ record.function + "] ";
		}
		msg += record.message;

		__android_log_print(priority, tag.c_str(), "%s", msg.c_str());
	}

}	 // namespace utility::logging

#endif	  // __ANDROID__
