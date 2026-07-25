#include "graphic/test_mesh.hpp"

#include "utility/graphic/mesh.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestMesh, EqualityAndInequality)
{
	VertexF vertex(
		PositionF(1.0, 2.0, 3.0), utility::math::Vector3F { 0.0, 1.0, 0.0 },
		utility::math::Vector2F { 0.5, 0.25 }, Color32Bit(10, 20, 30, 255));
	std::vector<VertexF> vertices { vertex };
	std::vector<uint32_t> indices { 0 };

	Mesh a(vertices, indices);
	Mesh b(vertices, indices);
	Mesh c(std::vector<VertexF> {}, std::vector<uint32_t> {});

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
	EXPECT_FALSE(a == c);
	EXPECT_TRUE(a != c);
}