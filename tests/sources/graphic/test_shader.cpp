#include "graphic/test_shader.hpp"

#include <string>

#include "utility/graphic/shader.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestShader, ConstructsWithAlignedBytecode)
{
	// 8 bytes = 2 SPIR-V words.
	std::string vert("\x03\x02\x23\x07\x00\x00\x00\x01", 8);
	std::string frag("\x03\x02\x23\x07\x00\x00\x00\x02", 8);

	Shader shader(vert, frag);
	ASSERT_EQ(shader.getVertexCode().size(), 2);
	ASSERT_EQ(shader.getFragmentCode().size(), 2);
	EXPECT_EQ(shader.getVertexCode()[0], 0x07230203u);
	EXPECT_EQ(shader.getFragmentCode()[0], 0x07230203u);
}

TEST_F(TestShader, RejectsMisalignedVertex)
{
	std::string vert("abc");	// 3 bytes, not a multiple of 4
	std::string frag("\x00\x00\x00\x00", 4);
	EXPECT_THROW(Shader(vert, frag), std::invalid_argument);
}

TEST_F(TestShader, RejectsMisalignedFragment)
{
	std::string vert("\x00\x00\x00\x00", 4);
	std::string frag("abcde");	  // 5 bytes, not a multiple of 4
	EXPECT_THROW(Shader(vert, frag), std::invalid_argument);
}
