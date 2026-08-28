#include "graphic/test_field_of_view.hpp"

#include "utility/graphic/field_of_view.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestFieldOfView, DefaultIsZero)
{
	FieldOfViewF fov;
	EXPECT_FLOAT_EQ(fov.getUp(), 0.0f);
	EXPECT_FLOAT_EQ(fov.getDown(), 0.0f);
	EXPECT_FLOAT_EQ(fov.getLeft(), 0.0f);
	EXPECT_FLOAT_EQ(fov.getRight(), 0.0f);
	EXPECT_TRUE(fov.isSymmetric());
}

TEST_F(TestFieldOfView, ConstructAndGet)
{
	FieldOfViewF fov(0.5f, 0.25f, 1.0f, 0.75f);
	EXPECT_FLOAT_EQ(fov.getUp(), 0.5f);
	EXPECT_FLOAT_EQ(fov.getDown(), 0.25f);
	EXPECT_FLOAT_EQ(fov.getLeft(), 1.0f);
	EXPECT_FLOAT_EQ(fov.getRight(), 0.75f);
}

TEST_F(TestFieldOfView, SettersReturnSelf)
{
	FieldOfViewF fov;
	fov.setUp(0.5f).setDown(0.5f).setLeft(0.25f).setRight(0.25f);
	EXPECT_FLOAT_EQ(fov.getUp(), 0.5f);
	EXPECT_FLOAT_EQ(fov.getDown(), 0.5f);
	EXPECT_FLOAT_EQ(fov.getLeft(), 0.25f);
	EXPECT_FLOAT_EQ(fov.getRight(), 0.25f);
}

TEST_F(TestFieldOfView, SymmetricDetection)
{
	FieldOfViewF symmetric(0.5f, 0.5f, 0.75f, 0.75f);
	EXPECT_TRUE(symmetric.isSymmetric());

	FieldOfViewF asymmetric(0.5f, 0.25f, 0.75f, 0.75f);
	EXPECT_FALSE(asymmetric.isSymmetric());
}

TEST_F(TestFieldOfView, SymmetryUsesEpsilon)
{
	FieldOfViewF fov(0.5f, 0.5f + 1e-7f, 0.75f, 0.75f);
	EXPECT_TRUE(fov.isSymmetric(1e-6f));
	EXPECT_FALSE(fov.isSymmetric(1e-8f));
}
