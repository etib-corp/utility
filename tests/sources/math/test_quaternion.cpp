#include "math/test_quaternion.hpp"

#include "utility/math/quaternion.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestQuaternion, Addition)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 4.0f, 3.0f, 2.0f, 1.0f };
	QuaternionF c = a + b;
	EXPECT_FLOAT_EQ(c.x, 5.0f);
	EXPECT_FLOAT_EQ(c.y, 5.0f);
	EXPECT_FLOAT_EQ(c.z, 5.0f);
	EXPECT_FLOAT_EQ(c.w, 5.0f);
}

TEST_F(TestQuaternion, Subtraction)
{
	QuaternionF a { 4.0f, 3.0f, 2.0f, 1.0f };
	QuaternionF b { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF c = a - b;
	EXPECT_FLOAT_EQ(c.x, 3.0f);
	EXPECT_FLOAT_EQ(c.y, 1.0f);
	EXPECT_FLOAT_EQ(c.z, -1.0f);
	EXPECT_FLOAT_EQ(c.w, -3.0f);
}

TEST_F(TestQuaternion, ScalarMultiplication)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF c = a * 2.0f;
	EXPECT_FLOAT_EQ(c.x, 2.0f);
	EXPECT_FLOAT_EQ(c.y, 4.0f);
	EXPECT_FLOAT_EQ(c.z, 6.0f);
	EXPECT_FLOAT_EQ(c.w, 8.0f);
}

TEST_F(TestQuaternion, Negation)
{
	QuaternionF a { 1.0f, -2.0f, 3.0f, -4.0f };
	QuaternionF c = -a;
	EXPECT_FLOAT_EQ(c.x, -1.0f);
	EXPECT_FLOAT_EQ(c.y, 2.0f);
	EXPECT_FLOAT_EQ(c.z, -3.0f);
	EXPECT_FLOAT_EQ(c.w, 4.0f);
}

TEST_F(TestQuaternion, Equality)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST_F(TestQuaternion, ConstructorMapsXyzwComponents)
{
	// The public API takes (x, y, z, w); the scalar component is last.
	QuaternionF q { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_FLOAT_EQ(q.x, 1.0f);
	EXPECT_FLOAT_EQ(q.y, 2.0f);
	EXPECT_FLOAT_EQ(q.z, 3.0f);
	EXPECT_FLOAT_EQ(q.w, 4.0f);
}

TEST_F(TestQuaternion, ExactEqualityRejectsRounding)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 1.0f, 2.0f, 3.0f, 4.000001f };
	EXPECT_FALSE(a == b);
}

TEST_F(TestQuaternion, EpsilonEqualityAcceptsTinyDifference)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 1.0f, 2.0f, 3.0f, 4.000001f };
	EXPECT_TRUE(a.equalsEpsilon(b));
}

TEST_F(TestQuaternion, EpsilonEqualityRejectsLargeDifference)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 1.5f, 2.0f, 3.0f, 4.0f };
	EXPECT_FALSE(a.equalsEpsilon(b));
}

TEST_F(TestQuaternion, Multiplication)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF b { 5.0f, 6.0f, 7.0f, 8.0f };
	QuaternionF c = a * b;
	EXPECT_FLOAT_EQ(c.x, 24.0f);
	EXPECT_FLOAT_EQ(c.y, 48.0f);
	EXPECT_FLOAT_EQ(c.z, 48.0f);
	EXPECT_FLOAT_EQ(c.w, -6.0f);
}

TEST_F(TestQuaternion, MultiplicationNotCommutative)
{
	QuaternionF a { 1.0f, 0.0f, 0.0f, 0.0f };
	QuaternionF b { 0.0f, 1.0f, 0.0f, 0.0f };
	EXPECT_NE(a * b, b * a);
}

TEST_F(TestQuaternion, AdditiveInverse)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	QuaternionF zero{ 0.0f, 0.0f, 0.0f, 0.0f };
	EXPECT_EQ(a + (-a), zero);
}

TEST_F(TestQuaternion, ScalarIdentity)
{
	QuaternionF a { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_EQ(a * 1.0f, a);
}
