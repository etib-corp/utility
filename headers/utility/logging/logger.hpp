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
		LogLevel _minLevel = LogLevel::DEBUG_LEVEL;

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
			std::ostringstream _stream;		   ///< Internal buffer
			bool _active;	 ///< False if level is below minimum

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
					_stream << std::forward<T>(value);
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
					_stream << manip;
				}
				return *this;
			}

			/**
			 * @brief Destructor emits the accumulated message via the parent
			 * logger.
			 */
			~LogMessage()
			{
				if (!_active || !_logger) {
					return;
				}
				LogRecord record;
				record.level	  = _level;
				record.message	  = _stream.str();
				record.timestamp  = Logger::getTimestamp();
				record.loggerName = _logger->getName();
				if (_level == LogLevel::DEBUG_LEVEL) {
					record.file		= _location.file_name();
					record.line		= static_cast<int>(_location.line());
					record.function = _location.function_name();
				}
				_logger->output(record);
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
		 * @brief Set the minimum log level. Messages below this level are
		 * suppressed.
		 * @param level Minimum level to emit.
		 */
		void setMinLevel(LogLevel level);

		/**
		 * @brief Get the current minimum log level.
		 * @return Minimum emitted level.
		 */
		LogLevel getMinLevel(void) const;

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
		 * @param level The log level.
		 * @return Integer value (Debug=0, Info=1, Warning=2, Error=3).
		 */
		static int levelValue(LogLevel level);

		/**
		 * @brief Begin a debug-level log message.
		 * @param loc Source location (auto-captured).
		 * @return LogMessage proxy for streaming.
		 */
		LogMessage
			debug(std::source_location loc = std::source_location::current())
		{
			return LogMessage(this, LogLevel::DEBUG_LEVEL, loc,
							  levelValue(LogLevel::DEBUG_LEVEL)
								  >= levelValue(_minLevel));
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
							  levelValue(LogLevel::INFO_LEVEL)
								  >= levelValue(_minLevel));
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
							  levelValue(LogLevel::WARNING_LEVEL)
								  >= levelValue(_minLevel));
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
							  levelValue(LogLevel::ERROR_LEVEL)
								  >= levelValue(_minLevel));
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
			return LogMessage(this, level, loc,
							  levelValue(level) >= levelValue(_minLevel));
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
