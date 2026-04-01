#include "graphic/test_vertex.hpp"

#include "utility/graphic/vertex.hpp"

using namespace utility::graphic;
using namespace utility::math;
using namespace tests::utility::graphic;

TEST_F(TestVertex, DefaultConstructor) {
  VertexF vertex;
  EXPECT_FLOAT_EQ(vertex.getPosition().getX(), 0.0f);
  EXPECT_FLOAT_EQ(vertex.getPosition().getY(), 0.0f);
  EXPECT_FLOAT_EQ(vertex.getPosition().getZ(), 0.0f);
}

TEST_F(TestVertex, SettersAndEquality) {
  VertexF a;
  VertexF b;

  PositionF position(1.0f, 2.0f, 3.0f);
  Vector3F normal{0.0f, 1.0f, 0.0f};
  Vector2F uv{0.5f, 0.25f};
  Color32Bit color(10, 20, 30, 255);

  a.setPosition(position);
  a.setNormal(normal);
  a.setTextureCoordinates(uv);
  a.setColor(color);

  b.setPosition(position);
  b.setNormal(normal);
  b.setTextureCoordinates(uv);
  b.setColor(color);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST_F(TestVertex, AttributeBatchSetterAndNormalCheck) {
  VertexF vertex;
  PositionF position(1.0f, 1.0f, 1.0f);
  Vector3F normal{0.0f, 1.0f, 0.0f};
  Vector2F uv{0.0f, 1.0f};
  Color32Bit color(1, 2, 3, 255);

  vertex.setAttributes(position, normal, uv, color);
  EXPECT_TRUE(vertex.hasUnitNormal());

  vertex.setNormal(Vector3F{0.0f, 2.0f, 0.0f});
  EXPECT_FALSE(vertex.hasUnitNormal());
}
