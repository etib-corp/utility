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

#include <gtest/gtest.h>

#include <atomic>
#include <iostream>
#include <regex>
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "utility/logging/logger.hpp"
#include "utility/logging/standard_logger.hpp"
#include "utility/logging/default_logger.hpp"

using utility::logging::DefaultLogger;
using utility::logging::FlushPolicy;
using utility::logging::Logger;
using utility::logging::LogLevel;
using utility::logging::LogRecord;
using utility::logging::StandardLogger;

namespace
{
	std::atomic<std::size_t> g_allocationCount { 0 };
}

// Replacement allocation functions used to assert that a suppressed message
// performs zero heap allocations. This intentionally instruments the whole
// test binary; the counter is only sampled immediately around the code under
// test.
void *operator new(std::size_t size)
{
	g_allocationCount.fetch_add(1, std::memory_order_relaxed);
	void *ptr = std::malloc(size == 0 ? 1 : size);
	if (ptr == nullptr) {
		throw std::bad_alloc();
	}
	return ptr;
}

void *operator new[](std::size_t size)
{
	return ::operator new(size);
}

void operator delete(void *ptr) noexcept
{
	std::free(ptr);
}

void operator delete[](void *ptr) noexcept
{
	std::free(ptr);
}

void operator delete(void *ptr, std::size_t) noexcept
{
	std::free(ptr);
}

void operator delete[](void *ptr, std::size_t) noexcept
{
	std::free(ptr);
}

namespace
{

	class TestLogger: public Logger
	{
		public:
		LogRecord lastRecord;
		bool called = false;

		TestLogger(const std::string &name)
			: Logger(name)
		{
		}

		void output(const LogRecord &record) override
		{
			lastRecord = record;
			called	   = true;
		}
	};

	/**
	 * @brief Force the `NO_COLOR` environment variable for the test scope so
	 * that `StandardLogger` emits deterministic, escape-free lines.
	 */
	class ScopedNoColor
	{
		public:
		ScopedNoColor()
		{
#if defined(_WIN32)
			_putenv_s("NO_COLOR", "1");
#else
			setenv("NO_COLOR", "1", 1);
#endif
		}

		~ScopedNoColor()
		{
#if defined(_WIN32)
			_putenv_s("NO_COLOR", "");
#else
			unsetenv("NO_COLOR");
#endif
		}
	};

	/**
	 * @brief Redirect an output stream's buffer for the test scope.
	 */
	class ScopedStreamCapture
	{
		public:
		explicit ScopedStreamCapture(std::ostream &stream)
			: _stream(stream)
			, _old(stream.rdbuf(_buffer.rdbuf()))
		{
		}

		~ScopedStreamCapture()
		{
			_stream.rdbuf(_old);
		}

		std::string str() const
		{
			return _buffer.str();
		}

		private:
		std::ostream &_stream;
		std::streambuf *_old;
		std::ostringstream _buffer;
	};

}	 // namespace

TEST(LoggerTest, StreamSingleValue)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);
	logger.debug() << "hello world";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "hello world");
	EXPECT_EQ(logger.lastRecord.level, LogLevel::DEBUG_LEVEL);
	EXPECT_EQ(logger.lastRecord.loggerName, "Test");
}

TEST(LoggerTest, StreamMultipleValues)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);
	logger.info() << "value=" << 42 << " done";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "value=42 done");
	EXPECT_EQ(logger.lastRecord.level, LogLevel::INFO_LEVEL);
}

TEST(LoggerTest, MessageIsOwnedNotAView)
{
	// A message exceeding the small-string optimization must still be owned
	// by the record after the `LogMessage` proxy is destroyed.
	TestLogger logger("Test");
	const std::string longText(256, 'x');
	logger.info() << longText;
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, longText);
}

TEST(LoggerTest, SourceLocationCaptured)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);
	logger.debug() << "loc test";
	EXPECT_TRUE(logger.called);
	EXPECT_NE(logger.lastRecord.file.find("test_logger.cpp"),
			  std::string::npos);
	EXPECT_GT(logger.lastRecord.line, 0);
	EXPECT_FALSE(logger.lastRecord.function.empty());
}

TEST(LoggerTest, SourceLocationSkippedForNonDebug)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);

	logger.info() << "info test";
	EXPECT_TRUE(logger.called);
	EXPECT_TRUE(logger.lastRecord.file.empty());
	EXPECT_EQ(logger.lastRecord.line, 0);
	EXPECT_TRUE(logger.lastRecord.function.empty());

	logger.called = false;
	logger.warning() << "warning test";
	EXPECT_TRUE(logger.called);
	EXPECT_TRUE(logger.lastRecord.file.empty());
	EXPECT_EQ(logger.lastRecord.line, 0);
	EXPECT_TRUE(logger.lastRecord.function.empty());

	logger.called = false;
	logger.error() << "error test";
	EXPECT_TRUE(logger.called);
	EXPECT_TRUE(logger.lastRecord.file.empty());
	EXPECT_EQ(logger.lastRecord.line, 0);
	EXPECT_TRUE(logger.lastRecord.function.empty());
}

TEST(LoggerTest, LevelFiltering)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::WARNING_LEVEL);

	logger.debug() << "suppressed";
	EXPECT_FALSE(logger.called);

	logger.info() << "suppressed";
	EXPECT_FALSE(logger.called);

	logger.warning() << "allowed";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "allowed");

	logger.called = false;
	logger.error() << "also allowed";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "also allowed");
}

TEST(LoggerTest, LogLevelValueOrder)
{
	EXPECT_LT(Logger::levelValue(LogLevel::DEBUG_LEVEL),
			  Logger::levelValue(LogLevel::INFO_LEVEL));
	EXPECT_LT(Logger::levelValue(LogLevel::INFO_LEVEL),
			  Logger::levelValue(LogLevel::WARNING_LEVEL));
	EXPECT_LT(Logger::levelValue(LogLevel::WARNING_LEVEL),
			  Logger::levelValue(LogLevel::ERROR_LEVEL));
}

TEST(LoggerTest, UnknownLevelMapsToHighSentinel)
{
	auto unknown = static_cast<LogLevel>(999);
	EXPECT_GT(Logger::levelValue(unknown),
			  Logger::levelValue(LogLevel::ERROR_LEVEL));
}

TEST(LoggerTest, DefaultLoggerIsStandardLogger)
{
	static_assert(
		std::is_same_v<DefaultLogger, StandardLogger>,
		"DefaultLogger should be StandardLogger on non-Android platforms");
}

TEST(StandardLoggerTest, LevelToString)
{
	EXPECT_EQ(Logger::levelToString(LogLevel::DEBUG_LEVEL), "Debug");
	EXPECT_EQ(Logger::levelToString(LogLevel::INFO_LEVEL), "Info");
	EXPECT_EQ(Logger::levelToString(LogLevel::WARNING_LEVEL), "Warning");
	EXPECT_EQ(Logger::levelToString(LogLevel::ERROR_LEVEL), "Error");
}

TEST(StandardLoggerTest, TimestampFormat)
{
	const std::string timestamp = Logger::getTimestamp();
	const std::regex pattern(
		R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}$)");
	EXPECT_TRUE(std::regex_match(timestamp, pattern)) << timestamp;
}

TEST(StandardLoggerTest, GoldenInfoLineFormat)
{
	ScopedNoColor noColor;
	const std::regex pattern(
		R"(^\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}\] \[Golden\] \[Info\] hello 42\n$)");

	std::string captured;
	{
		ScopedStreamCapture capture(std::cout);
		StandardLogger logger("Golden");
		logger.info() << "hello " << 42;
		captured = capture.str();
	}
	EXPECT_TRUE(std::regex_match(captured, pattern)) << captured;
}

TEST(StandardLoggerTest, GoldenDebugLineFormat)
{
	ScopedNoColor noColor;
	const std::regex pattern(
		R"(^\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}\] \[Golden\] \[Debug\] \[.*test_logger\.cpp:\d+ [^\]]+\] hello\n$)");

	std::string captured;
	{
		ScopedStreamCapture capture(std::cout);
		StandardLogger logger("Golden");
		logger.debug() << "hello";
		captured = capture.str();
	}
	EXPECT_TRUE(std::regex_match(captured, pattern)) << captured;
}

TEST(StandardLoggerTest, WarningAndErrorGoToStderr)
{
	ScopedNoColor noColor;
	const std::regex pattern(
		R"(^\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}\] \[Golden\] \[Error\] boom\n$)");

	std::string out;
	std::string err;
	{
		ScopedStreamCapture outCapture(std::cout);
		ScopedStreamCapture errCapture(std::cerr);
		StandardLogger logger("Golden");
		logger.error() << "boom";
		out = outCapture.str();
		err = errCapture.str();
	}
	EXPECT_TRUE(out.empty());
	EXPECT_TRUE(std::regex_match(err, pattern)) << err;
}

TEST(StandardLoggerTest, InfoGoesToStdout)
{
	ScopedNoColor noColor;

	std::string out;
	std::string err;
	{
		ScopedStreamCapture outCapture(std::cout);
		ScopedStreamCapture errCapture(std::cerr);
		StandardLogger logger("Golden");
		logger.info() << "plain";
		out = outCapture.str();
		err = errCapture.str();
	}
	EXPECT_TRUE(err.empty());
	EXPECT_NE(out.find("[Info] plain\n"), std::string::npos) << out;
}

TEST(LoggerTest, ConcurrentLoggingIsSafe)
{
	struct CountingLogger: Logger {
		std::atomic<int> count { 0 };
		CountingLogger(const std::string &name)
			: Logger(name)
		{
		}
		void output(const LogRecord &) override
		{
			++count;
		}
	};

	CountingLogger logger("Concurrent");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);
	constexpr int kThreads	 = 8;
	constexpr int kPerThread = 500;

	std::vector<std::thread> threads;
	for (int t = 0; t < kThreads; ++t) {
		threads.emplace_back([&]() {
			for (int i = 0; i < kPerThread; ++i) {
				logger.info() << "thread " << i;
			}
		});
	}
	for (auto &thread: threads) {
		thread.join();
	}
	EXPECT_EQ(logger.count.load(), kThreads * kPerThread);
}

TEST(LoggerTest, ThrowingOutputDoesNotTerminate)
{
	struct ThrowingLogger: Logger {
		ThrowingLogger(const std::string &name)
			: Logger(name)
		{
		}
		void output(const LogRecord &) override
		{
			throw std::runtime_error("boom");
		}
	};

	ThrowingLogger logger("Throw");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);
	EXPECT_NO_THROW({ logger.info() << "should not terminate"; });
}

TEST(LoggerTest, DefaultMinLevelFollowsBuildType)
{
#if defined(NDEBUG)
	EXPECT_EQ(Logger::defaultMinLevel(), LogLevel::WARNING_LEVEL);
#else
	EXPECT_EQ(Logger::defaultMinLevel(), LogLevel::DEBUG_LEVEL);
#endif

	// The constructor default is only overridden when the env var is set.
	if (std::getenv("UTILITY_LOG_LEVEL") == nullptr) {
		TestLogger logger("Test");
		EXPECT_EQ(logger.getMinLevel(), Logger::defaultMinLevel());
	}
}

TEST(LoggerTest, FlushPolicyDefaultsToBufferedAndRoundTrips)
{
	TestLogger logger("Test");
	EXPECT_EQ(logger.getFlushPolicy(), FlushPolicy::BUFFERED);

	logger.setFlushPolicy(FlushPolicy::ALWAYS);
	EXPECT_EQ(logger.getFlushPolicy(), FlushPolicy::ALWAYS);

	logger.setFlushPolicy(FlushPolicy::NEVER);
	EXPECT_EQ(logger.getFlushPolicy(), FlushPolicy::NEVER);
}

TEST(LoggerTest, SuppressedMessageDoesNotAllocate)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::WARNING_LEVEL);
	logger.called = false;

	const std::size_t before =
		g_allocationCount.load(std::memory_order_relaxed);
	logger.debug() << "suppressed " << 42 << " times";
	logger.info() << "suppressed too";
	const std::size_t after =
		g_allocationCount.load(std::memory_order_relaxed);

	EXPECT_EQ(before, after);
	EXPECT_FALSE(logger.called);
}

TEST(LoggerTest, ActiveMessageAllocates)
{
	TestLogger logger("Test");
	logger.setMinLevel(LogLevel::DEBUG_LEVEL);

	const std::size_t before =
		g_allocationCount.load(std::memory_order_relaxed);
	logger.debug() << "active " << 42;
	const std::size_t after =
		g_allocationCount.load(std::memory_order_relaxed);

	EXPECT_GT(after, before);
	EXPECT_TRUE(logger.called);
}

TEST(LoggerTest, MinLevelWritesAreRaceFree)
{
	TestLogger logger("Test");
	std::atomic<bool> stop { false };

	// Level writes race with the accessor reads; the sanitizer CI build
	// (TSan) is what actually guards against the previous data race.
	std::thread writer([&]() {
		for (int i = 0; i < 1000; ++i) {
			logger.setMinLevel(LogLevel::ERROR_LEVEL);
			logger.setMinLevel(LogLevel::DEBUG_LEVEL);
		}
		stop.store(true, std::memory_order_relaxed);
	});
	while (!stop.load(std::memory_order_relaxed)) {
		logger.debug() << "racer";
	}
	writer.join();
	SUCCEED();
}
