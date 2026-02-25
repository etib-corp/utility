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

#include "logging/test_file_logger.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

TEST_F(TestFileLogger, CreatesAndOpensLogFile) {
	std::filesystem::create_directories("logs");

	std::string name = "file_logger_open_test";
	const std::filesystem::path expectedPath =
			std::filesystem::path("logs") / (name + ".log");
	std::filesystem::remove(expectedPath);

	utility::logging::FileLogger logger(name);

	EXPECT_TRUE(logger.isOpen());
	EXPECT_EQ(std::filesystem::path(logger.getFilePath()), expectedPath);
}

TEST_F(TestFileLogger, WritesMessagesToDisk) {
	std::filesystem::create_directories("logs");

	std::string name = "file_logger_write_test";
	const std::filesystem::path path = std::filesystem::path("logs") /
																		 (name + ".log");
	std::filesystem::remove(path);

	{
		utility::logging::FileLogger logger(name);
		logger.info("hello file logger");
		logger.error("error line");
	}

	std::ifstream input(path);
	ASSERT_TRUE(input.is_open());

	std::stringstream content;
	content << input.rdbuf();
	const std::string text = content.str();

	EXPECT_NE(text.find("[INFO]"), std::string::npos);
	EXPECT_NE(text.find("hello file logger"), std::string::npos);
	EXPECT_NE(text.find("[ERROR]"), std::string::npos);
	EXPECT_NE(text.find("error line"), std::string::npos);
}