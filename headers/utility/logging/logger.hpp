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
 * @file logger.hpp
 * @brief Logging interface with levels, source-location metadata, and
 * stream-style output.
 *
 * Defines the `utility::Logger` abstract base class along with the `LogLevel`
 * enumeration and `LogRecord`. Concrete loggers derive from `Logger` and
 * implement `output(const LogRecord&)`.
 *
 * Usage:
 *   getLogger().debug() << "Entity " << id << " updated";
 */

#pragma once

#include <atomic>
#include <limits>
#include <memory>
#include <mutex>
#include <source_location>
#include <sstream>
#include <string>
#include <type_traits>

namespace utility::logging
{

	/**
	 * @brief Log severity levels.
	 */
	enum class LogLevel {
		DEBUG_LEVEL,	  ///< Detailed debugging information
		INFO_LEVEL,		  ///< General informational messages
		WARNING_LEVEL,	  ///< Warning messages for potentially harmful
						  ///< situations
		ERROR_LEVEL		  ///< Error messages for serious problems
	};

	/**
	 * @brief Controls when a stream-backed logger flushes its output.
	 *
	 * Buffering avoids a per-line flush (`std::endl`) while still guaranteeing
	 * that warnings and errors reach the console promptly.
	 */
	enum class FlushPolicy {
		BUFFERED,	///< Buffer debug/info; flush warnings/errors (default)
		ALWAYS,		///< Flush after every message (legacy behavior)
		NEVER		///< Never flush except on destruction
	};

	/**
	 * @brief Structured log record carrying metadata for a single log entry.
	 */
	struct LogRecord {
		LogLevel level;			  ///< Severity level
		std::string message;	  ///< Log message content
		std::string timestamp;	  ///< Formatted timestamp string
		std::string
			loggerName;			 ///< Name of the logger that emitted the record
		std::string file;		 ///< Source file path
		int line = 0;			 ///< Source line number
		std::string function;	 ///< Function name
	};

	/**
	 * @brief Abstract logger interface defining stream-style logging
	 * operations.
	 *
	 * Implementations derive from `Logger` and override `output(const
	 * LogRecord&)` to handle formatted output.
	 */
	class Logger
	{
		private:
		std::string _name;	  ///< Logger name
		std::atomic<LogLevel> _minLevel {
			defaultMinLevel()
		};	  ///< Minimum emitted level (lock-free)
		std::atomic<FlushPolicy> _flushPolicy {
			FlushPolicy::BUFFERED
		};	  ///< Stream flush policy (ignored by non-stream loggers)

		/**
		 * @brief Lock-free check whether a level passes the current minimum.
		 *
		 * The check is performed before any allocation so a suppressed message
		 * costs only a relaxed atomic load and an integer comparison.
		 *
		 * @param level The level to test.
		 * @return True if the level should be emitted.
		 */
		bool isEnabled(LogLevel level) const noexcept
		{
			return levelValue(level)
				>= levelValue(_minLevel.load(std::memory_order_relaxed));
		}

		protected:
		mutable std::mutex _mutex;	  ///< Serializes output access

		public:
		/**
		 * @brief Proxy object returned by debug/info/warning/error.
		 *
		 * Accumulates streamed data and flushes a `LogRecord` to the parent
		 * `Logger` on destruction.
		 */
		class LogMessage
		{
			private:
			Logger *_logger;				   ///< Parent logger
			LogLevel _level;				   ///< Severity level
			std::source_location _location;	   ///< Call-site metadata
			std::unique_ptr<std::ostringstream>
				_stream;	 ///< Lazily allocated internal buffer
			bool _active;	 ///< False if level is below minimum

			/**
			 * @brief Ensure the stream buffer is allocated.
			 * @return Reference to the internal stream.
			 */
			std::ostringstream &ensureStream(void)
			{
				if (!_stream) {
					_stream = std::make_unique<std::ostringstream>();
				}
				return *_stream;
			}

			public:
			/**
			 * @brief Construct a LogMessage.
			 * @param logger Parent logger pointer.
			 * @param level Severity level.
			 * @param loc Source location of the call site.
			 * @param active Whether the message should actually be emitted.
			 */
			LogMessage(Logger *logger, LogLevel level, std::source_location loc,
					   bool active)
				: _logger(logger)
				, _level(level)
				, _location(loc)
				, _active(active)
			{
			}

			/**
			 * @brief Stream any value into the log buffer.
			 * @tparam T Type of the streamed value.
			 * @param value Value to append.
			 * @return Reference to this LogMessage for chaining.
			 */
			template<typename T> LogMessage &operator<<(T &&value)
			{
				if (_active) {
					ensureStream() << std::forward<T>(value);
				}
				return *this;
			}

			/**
			 * @brief Stream an ostream manipulator (e.g. std::endl).
			 * @param manip Manipulator function pointer.
			 * @return Reference to this LogMessage for chaining.
			 */
			LogMessage &operator<<(std::ostream &(*manip)(std::ostream &))
			{
				if (_active) {
					ensureStream() << manip;
				}
				return *this;
			}

			/**
			 * @brief Destructor emits the accumulated message via the parent
			 * logger.
			 *
			 * Output is guarded so an exception thrown by a logger
			 * implementation cannot terminate the process, even during stack
			 * unwinding.
			 */
			~LogMessage()
			{
				if (!_active || !_logger || !_stream) {
					return;
				}
				LogRecord record;
				record.level	  = _level;
				record.message	  = _stream->str();
				record.timestamp  = Logger::getTimestamp();
				record.loggerName = _logger->getName();
				if (_level == LogLevel::DEBUG_LEVEL) {
					record.file		= _location.file_name();
					record.line		= static_cast<int>(_location.line());
					record.function = _location.function_name();
				}
				std::lock_guard<std::mutex> guard(_logger->_mutex);
				try {
					_logger->output(record);
				} catch (...) {
					// Logging must never become a terminate path.
				}
			}
		};

		public:
		/**
		 * @brief Default constructor.
		 * @param name The name of the logger.
		 */
		Logger(const std::string &name);

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~Logger(void) = default;

		/**
		 * @brief Default minimum level for the current build type.
		 *
		 * Release builds (`NDEBUG`) default to `WARNING_LEVEL` so hot-loop
		 * `debug`/`info` calls are suppressed; debug builds keep
		 * `DEBUG_LEVEL`. The `UTILITY_LOG_LEVEL` environment variable
		 * (`debug`/`info`/`warning`/`error`) overrides this at construction.
		 *
		 * @return The default minimum level.
		 */
		static constexpr LogLevel defaultMinLevel(void) noexcept
		{
#if defined(NDEBUG)
			return LogLevel::WARNING_LEVEL;
#else
			return LogLevel::DEBUG_LEVEL;
#endif
		}

		/**
		 * @brief Set the minimum log level. Messages below this level are
		 * suppressed.
		 * @param level Minimum level to emit.
		 */
		void setMinLevel(LogLevel level) noexcept;

		/**
		 * @brief Get the current minimum log level.
		 * @return Minimum emitted level.
		 */
		LogLevel getMinLevel(void) const noexcept;

		/**
		 * @brief Set the output flush policy.
		 * @param policy The flush policy to apply.
		 */
		void setFlushPolicy(FlushPolicy policy) noexcept;

		/**
		 * @brief Get the current output flush policy.
		 * @return The active flush policy.
		 */
		FlushPolicy getFlushPolicy(void) const noexcept;

		/**
		 * @brief Get string representation of log level.
		 * @param level The log level to convert.
		 * @return String representation of the level.
		 */
		static std::string levelToString(LogLevel level);

		/**
		 * @brief Get current timestamp as formatted string.
		 * @return Formatted timestamp string.
		 */
		static std::string getTimestamp(void);

		/**
		 * @brief Get numeric value of a log level for comparison.
		 *
		 * Inline and `constexpr` so the call-site filter is a single
		 * comparison that the optimizer can fold.
		 *
		 * @param level The log level.
		 * @return Integer value (Debug=0, Info=1, Warning=2, Error=3); unknown
		 * levels map to a high sentinel so they are never silently dropped.
		 */
		static constexpr int levelValue(LogLevel level) noexcept
		{
			switch (level) {
				case LogLevel::DEBUG_LEVEL:
					return 0;
				case LogLevel::INFO_LEVEL:
					return 1;
				case LogLevel::WARNING_LEVEL:
					return 2;
				case LogLevel::ERROR_LEVEL:
					return 3;
				default:
					// Return a high sentinel so an unknown/future level is
					// treated as most severe and never silently dropped.
					return std::numeric_limits<int>::max();
			}
		}

		/**
		 * @brief Begin a debug-level log message.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			debug(std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, LogLevel::DEBUG_LEVEL, loc,
							  isEnabled(LogLevel::DEBUG_LEVEL));
		}

		/**
		 * @brief Begin an info-level log message.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			info(std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, LogLevel::INFO_LEVEL, loc,
							  isEnabled(LogLevel::INFO_LEVEL));
		}

		/**
		 * @brief Begin a warning-level log message.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			warning(std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, LogLevel::WARNING_LEVEL, loc,
							  isEnabled(LogLevel::WARNING_LEVEL));
		}

		/**
		 * @brief Begin an error-level log message.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			error(std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, LogLevel::ERROR_LEVEL, loc,
							  isEnabled(LogLevel::ERROR_LEVEL));
		}

		/**
		 * @brief Begin a log message with dynamic level.
		 * @param level Severity level.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			log(LogLevel level,
				std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, level, loc, isEnabled(level));
		}

		/**
		 * @brief Output a fully-formed log record.
		 * @param record The log record to output.
		 */
		virtual void output(const LogRecord &record) = 0;

		/**
		 * @brief Get the logger name.
		 * @return The name of this logger.
		 */
		const std::string &getName(void) const
		{
			return _name;
		}
	};

	/**
	 * @brief Concept to ensure a type inherits from Logger.
	 * @tparam Type The type to check.
	 */
	template<typename Type>
	concept InheritFromLogger = std::is_base_of_v<Logger, Type>;

}	 // namespace utility::logging
