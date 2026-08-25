#include "test_file.hpp"

#include <cstddef>

#include "utility/system_io/file.hpp"

using namespace utility;

namespace tests::utility
{

	TEST_F(TestFile, StoresBinaryContent)
	{
		std::string content;
		content.push_back('a');
		content.push_back('b');
		content.push_back('\0');
		content.push_back('c');
		content.push_back('d');
		File file("/tmp/bin.dat", content);
		EXPECT_EQ(file.size(), 5);
		EXPECT_EQ(file.data()[2], std::byte { 0 });
	}

	TEST_F(TestFile, TextContentView)
	{
		File file("/tmp/asset.txt", "hello");
		EXPECT_EQ(file.content(), "hello");
	}

	TEST_F(TestFile, DataAndTextViewAgree)
	{
		File file("/tmp/asset.txt", "hello");
		EXPECT_EQ(file.content().size(), file.size());
		EXPECT_EQ(file.content()[0], 'h');
	}

}	 // namespace tests::utility
