#include "math/test_matrix.hpp"

#include "utility/math/matrix.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestMatrix, DefaultConstructsIdentityForSquare)
{
	Matrix3x3F m;
	Matrix3x3F expected {
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	EXPECT_EQ(m, expected);
}

TEST_F(TestMatrix, DefaultConstructsZeroForNonSquare)
{
	Matrix4x3F m;
	Matrix4x3F expected { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	EXPECT_EQ(m, expected);
}

TEST_F(TestMatrix, Addition)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	Matrix3x3F c = a + b;
	EXPECT_FLOAT_EQ(c[0][0], 10.0f);
	EXPECT_FLOAT_EQ(c[1][1], 10.0f);
	EXPECT_FLOAT_EQ(c[2][2], 10.0f);
}

TEST_F(TestMatrix, Subtraction)
{
	Matrix3x3F a { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	Matrix3x3F b { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F c = a - b;
	EXPECT_FLOAT_EQ(c[0][0], 8.0f);
	EXPECT_FLOAT_EQ(c[1][1], 0.0f);
	EXPECT_FLOAT_EQ(c[2][2], -8.0f);
}

TEST_F(TestMatrix, ScalarMultiplication)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F c = a * 2.0f;
	EXPECT_FLOAT_EQ(c[0][0], 2.0f);
	EXPECT_FLOAT_EQ(c[1][1], 10.0f);
	EXPECT_FLOAT_EQ(c[2][2], 18.0f);
}

TEST_F(TestMatrix, ScalarDivision)
{
	Matrix3x3F a { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f };
	Matrix3x3F c = a / 2.0f;
	EXPECT_FLOAT_EQ(c[0][0], 1.0f);
	EXPECT_FLOAT_EQ(c[1][1], 5.0f);
	EXPECT_FLOAT_EQ(c[2][2], 9.0f);
}

TEST_F(TestMatrix, MatrixMultiplicationFullCheck)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	Matrix3x3F c = a * b;
	EXPECT_NEAR(c[0][0], 30.0f, 1e-5f);
	EXPECT_NEAR(c[1][0], 24.0f, 1e-5f);
	EXPECT_NEAR(c[2][0], 18.0f, 1e-5f);
	EXPECT_NEAR(c[0][1], 84.0f, 1e-5f);
	EXPECT_NEAR(c[1][1], 69.0f, 1e-5f);
	EXPECT_NEAR(c[2][1], 54.0f, 1e-5f);
	EXPECT_NEAR(c[0][2], 138.0f, 1e-5f);
	EXPECT_NEAR(c[1][2], 114.0f, 1e-5f);
	EXPECT_NEAR(c[2][2], 90.0f, 1e-5f);
}

TEST_F(TestMatrix, IdentityProperty)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F id =
		Matrix3x3F { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	Matrix3x3F leftId  = id * a;
	Matrix3x3F rightId = a * id;
	EXPECT_EQ(leftId, a);
	EXPECT_EQ(rightId, a);
}

TEST_F(TestMatrix, AssociativityProperty)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	Matrix3x3F c { 2.0f, 0.0f, 1.0f, 3.0f, 1.0f, 0.0f, 0.0f, 2.0f, 4.0f };
	Matrix3x3F lhs = (a * b) * c;
	Matrix3x3F rhs = a * (b * c);
	EXPECT_EQ(lhs, rhs);
}

TEST_F(TestMatrix, AdditionCommutative)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	EXPECT_EQ(a + b, b + a);
}

TEST_F(TestMatrix, ConstructorRequiresExactCount)
{
	EXPECT_THROW(Matrix3x3F({ 1.0f, 2.0f, 3.0f }), std::invalid_argument);
}

TEST_F(TestMatrix, MatrixMultiplicationNotCommutativeInGeneral)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	EXPECT_NE(a * b, b * a);
}

TEST_F(TestMatrix, IdentityScalarMultiplication)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	EXPECT_EQ(a * 1.0f, a);
}

TEST_F(TestMatrix, ZeroScalarMultiplication)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F expected {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	EXPECT_EQ(a * 0.0f, expected);
}

TEST_F(TestMatrix, AdditiveInverse)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F zero { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	EXPECT_EQ(a + (-a), zero);
}

TEST_F(TestMatrix, Negation)
{
	Matrix3x3F a { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, -6.0f, 7.0f, -8.0f, 9.0f };
	Matrix3x3F c = -a;
	EXPECT_FLOAT_EQ(c[0][0], -1.0f);
	EXPECT_FLOAT_EQ(c[1][1], -5.0f);
	EXPECT_FLOAT_EQ(c[2][2], -9.0f);
}

TEST_F(TestMatrix, Equality)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST_F(TestMatrix, ScalarDivisionByZeroThrows)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	EXPECT_THROW(a / 0.0f, std::invalid_argument);
	EXPECT_THROW(a /= 0.0f, std::invalid_argument);
}

TEST_F(TestMatrix, ExactEqualityRejectsRounding)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.000001f };
	EXPECT_FALSE(a == b);
}

TEST_F(TestMatrix, EpsilonEqualityAcceptsTinyDifference)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.000001f };
	EXPECT_TRUE(a.equalsEpsilon(b));
}

TEST_F(TestMatrix, EpsilonEqualityRejectsLargeDifference)
{
	Matrix3x3F a { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	Matrix3x3F b { 2.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	EXPECT_FALSE(a.equalsEpsilon(b));
}

TEST_F(TestMatrix, NonSquareMultiplication)
{
	Matrix2x3F lhs { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
	Matrix3x2F rhs { 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f };
	auto result = lhs * rhs;
	EXPECT_NEAR(result[0][0], 27.0f, 1e-5f);
	EXPECT_NEAR(result[1][1], 68.0f, 1e-5f);
	EXPECT_NEAR(result[2][2], 117.0f, 1e-5f);
}
