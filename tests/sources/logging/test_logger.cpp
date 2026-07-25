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

#include "utility/logging/logger.hpp"
#include "utility/logging/standard_logger.hpp"
#include "utility/logging/default_logger.hpp"

using utility::logging::DefaultLogger;
using utility::logging::Logger;
using utility::logging::LogLevel;
using utility::logging::LogRecord;
using utility::logging::StandardLogger;

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

}	 // namespace

TEST(LoggerTest, StreamSingleValue)
{
	TestLogger logger("Test");
	logger.debug() << "hello world";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "hello world");
	EXPECT_EQ(logger.lastRecord.level, LogLevel::DEBUG_LEVEL);
	EXPECT_EQ(logger.lastRecord.loggerName, "Test");
}

TEST(LoggerTest, StreamMultipleValues)
{
	TestLogger logger("Test");
	logger.info() << "value=" << 42 << " done";
	EXPECT_TRUE(logger.called);
	EXPECT_EQ(logger.lastRecord.message, "value=42 done");
	EXPECT_EQ(logger.lastRecord.level, LogLevel::INFO_LEVEL);
}

TEST(LoggerTest, SourceLocationCaptured)
{
	TestLogger logger("Test");
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
