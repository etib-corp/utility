#include "test_file.hpp"

#include "utility/system_io/file.hpp"

using namespace utility;

namespace tests::utility
{

	TEST_F(TestFile, InitialState)
	{
		File file("/tmp/asset.bin", "hello");
		EXPECT_EQ(file.path(), "/tmp/asset.bin");
		EXPECT_EQ(file.content(), "hello");
		EXPECT_EQ(file.size(), 5);
		EXPECT_EQ(file.tell(), 0);
	}

	TEST_F(TestFile, ReadIntoBuffer)
	{
		File file("/tmp/asset.bin", "abcdef");
		char buffer[6] = {};
		size_t n = file.read(buffer, 1, 6);
		EXPECT_EQ(n, 6);
		EXPECT_EQ(std::string(buffer, 6), "abcdef");
		EXPECT_EQ(file.tell(), 6);
	}

	TEST_F(TestFile, ReadPastEndClamps)
	{
		File file("/tmp/asset.bin", "abc");
		char buffer[10] = {};
		size_t n = file.read(buffer, 1, 10);
		EXPECT_EQ(n, 3);
		EXPECT_EQ(file.tell(), 3);
	}

	TEST_F(TestFile, ReadIntoString)
	{
		File file("/tmp/asset.bin", "xyz");
		std::string out;
		size_t n = file.read(out, 1, 2);
		EXPECT_EQ(n, 2);
		EXPECT_EQ(out, "xy");
	}

	TEST_F(TestFile, WriteInsertsAtPosition)
	{
		File file("/tmp/asset.bin", "ab");
		size_t n = file.write("cd", 1, 2);
		EXPECT_EQ(n, 2);
		EXPECT_EQ(file.content(), "cdab");
		EXPECT_EQ(file.tell(), 2);
	}

	TEST_F(TestFile, WriteAppendsAtEnd)
	{
		File file("/tmp/asset.bin", "ab");
		file.seek(0, File::Seek::END);
		size_t n = file.write("cd", 1, 2);
		EXPECT_EQ(n, 2);
		EXPECT_EQ(file.content(), "abcd");
		EXPECT_EQ(file.tell(), 4);
	}

	TEST_F(TestFile, SeekModes)
	{
		File file("/tmp/asset.bin", "abcdef");
		EXPECT_EQ(file.seek(2, File::Seek::SET), 0);
		EXPECT_EQ(file.tell(), 2);
		EXPECT_EQ(file.seek(1, File::Seek::CUR), 0);
		EXPECT_EQ(file.tell(), 3);
		EXPECT_EQ(file.seek(-1, File::Seek::END), 0);
		EXPECT_EQ(file.tell(), 5);
	}

	TEST_F(TestFile, SeekNegativeRejected)
	{
		File file("/tmp/asset.bin", "abcdef");
		EXPECT_EQ(file.seek(-5, File::Seek::SET), -1);
		EXPECT_EQ(file.tell(), 0);
	}

	TEST_F(TestFile, SeekUnknownRejected)
	{
		File file("/tmp/asset.bin", "abcdef");
		EXPECT_EQ(file.seek(0, static_cast<File::Seek>(99)), -1);
	}

	TEST_F(TestFile, ClearResets)
	{
		File file("/tmp/asset.bin", "abcdef");
		file.seek(3, File::Seek::SET);
		file.clear();
		EXPECT_TRUE(file.content().empty());
		EXPECT_EQ(file.size(), 0);
		EXPECT_EQ(file.tell(), 0);
	}

	TEST_F(TestFile, RemoveErasesFromPosition)
	{
		File file("/tmp/asset.bin", "abcdef");
		file.seek(2, File::Seek::SET);
		size_t n = file.remove(2);
		EXPECT_EQ(n, 2);
		EXPECT_EQ(file.content(), "abef");
	}

}	 // namespace tests::utility
