#include "graphic/test_code_points.hpp"

#include "utility/graphic/text/code_points.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestCodePoints, ParseAndLookup)
{
	CodePoints codes("space 0x20\nA 0x41\neuro 20ac\n");
	EXPECT_EQ(codes.getCode("space"), 0x20);
	EXPECT_EQ(codes.getCode("A"), 0x41);
	EXPECT_EQ(codes.getCode("euro"), 0x20AC);
}

TEST_F(TestCodePoints, MissingNameReturnsZero)
{
	CodePoints codes("A 41\n");
	EXPECT_EQ(codes.getCode("missing"), 0);
}

TEST_F(TestCodePoints, EmptyContentYieldsNoCodes)
{
	CodePoints codes("");
	EXPECT_EQ(codes.getCode("A"), 0);
}

TEST_F(TestCodePoints, ToUtf8Ascii)
{
	EXPECT_EQ(CodePoints::toUtf8(0x41), std::string("A"));
}

TEST_F(TestCodePoints, ToUtf8TwoByte)
{
	EXPECT_EQ(CodePoints::toUtf8(0xE9), std::string("\xC3\xA9"));
}

TEST_F(TestCodePoints, ToUtf8ThreeByte)
{
	EXPECT_EQ(CodePoints::toUtf8(0x20AC), std::string("\xE2\x82\xAC"));
}

TEST_F(TestCodePoints, ToUtf8FourByte)
{
	EXPECT_EQ(CodePoints::toUtf8(0x1F600),
			  std::string("\xF0\x9F\x98\x80"));
}
