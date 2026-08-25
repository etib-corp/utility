#include "math/test_vector.hpp"

#include <cmath>

#include "utility/math/vector.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestVector, Addition)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 4.0f, 5.0f, 6.0f };
	Vector3F c = a + b;
	EXPECT_FLOAT_EQ(c[0], 5.0f);
	EXPECT_FLOAT_EQ(c[1], 7.0f);
	EXPECT_FLOAT_EQ(c[2], 9.0f);
}

TEST_F(TestVector, Subtraction)
{
	Vector3F a { 4.0f, 5.0f, 6.0f };
	Vector3F b { 1.0f, 2.0f, 3.0f };
	Vector3F c = a - b;
	EXPECT_FLOAT_EQ(c[0], 3.0f);
	EXPECT_FLOAT_EQ(c[1], 3.0f);
	EXPECT_FLOAT_EQ(c[2], 3.0f);
}

TEST_F(TestVector, ScalarMultiplication)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F c = a * 2.0f;
	EXPECT_FLOAT_EQ(c[0], 2.0f);
	EXPECT_FLOAT_EQ(c[1], 4.0f);
	EXPECT_FLOAT_EQ(c[2], 6.0f);
}

TEST_F(TestVector, ScalarDivision)
{
	Vector3F a { 2.0f, 4.0f, 6.0f };
	Vector3F c = a / 2.0f;
	EXPECT_FLOAT_EQ(c[0], 1.0f);
	EXPECT_FLOAT_EQ(c[1], 2.0f);
	EXPECT_FLOAT_EQ(c[2], 3.0f);
}

TEST_F(TestVector, ElementwiseMultiplication)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 4.0f, 5.0f, 6.0f };
	Vector3F c = a * b;
	EXPECT_FLOAT_EQ(c[0], 4.0f);
	EXPECT_FLOAT_EQ(c[1], 10.0f);
	EXPECT_FLOAT_EQ(c[2], 18.0f);
}

TEST_F(TestVector, ElementwiseDivision)
{
	Vector3F a { 4.0f, 9.0f, 16.0f };
	Vector3F b { 2.0f, 3.0f, 4.0f };
	Vector3F c = a / b;
	EXPECT_FLOAT_EQ(c[0], 2.0f);
	EXPECT_FLOAT_EQ(c[1], 3.0f);
	EXPECT_FLOAT_EQ(c[2], 4.0f);
}

TEST_F(TestVector, Negation)
{
	Vector3F a { 1.0f, -2.0f, 3.0f };
	Vector3F c = -a;
	EXPECT_FLOAT_EQ(c[0], -1.0f);
	EXPECT_FLOAT_EQ(c[1], 2.0f);
	EXPECT_FLOAT_EQ(c[2], -3.0f);
}

TEST_F(TestVector, Equality)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 1.0f, 2.0f, 3.0f };
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST_F(TestVector, AdditionCommutative)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 4.0f, 5.0f, 6.0f };
	EXPECT_EQ(a + b, b + a);
}

TEST_F(TestVector, AdditionAssociative)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 4.0f, 5.0f, 6.0f };
	Vector3F c { 7.0f, 8.0f, 9.0f };
	EXPECT_EQ((a + b) + c, a + (b + c));
}

TEST_F(TestVector, AdditiveIdentity)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F zero{ 0.0f, 0.0f, 0.0f };
	EXPECT_EQ(a + zero, a);
	EXPECT_EQ(zero + a, a);
}

TEST_F(TestVector, AdditiveInverse)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F zero{ 0.0f, 0.0f, 0.0f };
	EXPECT_EQ(a + (-a), zero);
}

TEST_F(TestVector, ScalarIdentity)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	EXPECT_EQ(a * 1.0f, a);
}

TEST_F(TestVector, ScalarDistributivity)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F b { 4.0f, 5.0f, 6.0f };
	EXPECT_EQ(2.0f * (a + b), (2.0f * a) + (2.0f * b));
}

TEST_F(TestVector, ConstructorRequiresExactDimension)
{
	EXPECT_THROW(Vector3F({ 1.0f, 2.0f }), std::invalid_argument);
	EXPECT_THROW(Vector3F({ 1.0f, 2.0f, 3.0f, 4.0f }), std::invalid_argument);
}

TEST_F(TestVector, ElementwiseDivisionByZero)
{
	Vector3F a { 1.0f, 2.0f, 3.0f };
	Vector3F zero{ 0.0f, 0.0f, 0.0f };
	Vector3F c = a / zero;
	EXPECT_TRUE(std::isinf(c[0]));
	EXPECT_TRUE(std::isinf(c[1]));
	EXPECT_TRUE(std::isinf(c[2]));
}
