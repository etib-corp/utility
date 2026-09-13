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

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>

#include "utility/logging/logger.hpp"

namespace utility::logging
{

	namespace
	{
		/**
		 * @brief Parse a case-insensitive level name.
		 * @param text Level name (debug/info/warning/error).
		 * @param fallback Value returned when @p text is null or unknown.
		 * @return The parsed level, or @p fallback.
		 */
		LogLevel parseLevel(const char *text, LogLevel fallback)
		{
			if (text == nullptr) {
				return fallback;
			}
			std::string value(text);
			std::transform(value.begin(), value.end(), value.begin(),
						   [](unsigned char c) {
							   return static_cast<char>(std::tolower(c));
						   });
			if (value == "debug") {
				return LogLevel::DEBUG_LEVEL;
			}
			if (value == "info") {
				return LogLevel::INFO_LEVEL;
			}
			if (value == "warning") {
				return LogLevel::WARNING_LEVEL;
			}
			if (value == "error") {
				return LogLevel::ERROR_LEVEL;
			}
			return fallback;
		}
	}	 // namespace

	std::string Logger::levelToString(LogLevel level)
	{
		switch (level) {
			case LogLevel::DEBUG_LEVEL:
				return "Debug";
			case LogLevel::INFO_LEVEL:
				return "Info";
			case LogLevel::WARNING_LEVEL:
				return "Warning";
			case LogLevel::ERROR_LEVEL:
				return "Error";
			default:
				return "Unknown";
		}
	}

	std::string Logger::getTimestamp()
	{
		auto now  = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		auto ms	  = std::chrono::duration_cast<std::chrono::milliseconds>(
						now.time_since_epoch())
			% 1000;

		std::tm local {};
#if defined(_WIN32)
		localtime_s(&local, &time);
#else
		localtime_r(&time, &local);
#endif

		std::stringstream ss;
		ss << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
		ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
		return ss.str();
	}

	Logger::Logger(const std::string &name)
		: _name(name)
	{
		// Allow deployments to restore verbosity without a recompile.
		const char *envLevel = std::getenv("UTILITY_LOG_LEVEL");
		if (envLevel != nullptr) {
			_minLevel.store(
				parseLevel(envLevel,
						   _minLevel.load(std::memory_order_relaxed)),
				std::memory_order_relaxed);
		}
	}

	void Logger::setMinLevel(LogLevel level) noexcept
	{
		_minLevel.store(level, std::memory_order_relaxed);
	}

	LogLevel Logger::getMinLevel(void) const noexcept
	{
		return _minLevel.load(std::memory_order_relaxed);
	}

	void Logger::setFlushPolicy(FlushPolicy policy) noexcept
	{
		_flushPolicy.store(policy, std::memory_order_relaxed);
	}

	FlushPolicy Logger::getFlushPolicy(void) const noexcept
	{
		return _flushPolicy.load(std::memory_order_relaxed);
	}

}	 // namespace utility::logging
