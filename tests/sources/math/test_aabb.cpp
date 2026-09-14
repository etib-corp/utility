#include "math/test_aabb.hpp"

#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include <span>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "utility/math/aabb.hpp"

using namespace utility::math;
using namespace tests::utility::math;

TEST_F(TestAabb, AliasesMatchComponentTypes)
{
	static_assert(std::is_same_v<AabbF, Aabb<float>>);
	static_assert(std::is_same_v<AabbD, Aabb<double>>);
	SUCCEED();
}

TEST_F(TestAabb, DefaultConstructedIsEmpty)
{
	AabbF box;
	EXPECT_TRUE(box.isEmpty());
}

TEST_F(TestAabb, ConstructedFromMinMaxIsNotEmpty)
{
	AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	EXPECT_FALSE(box.isEmpty());
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 1.0f, 1.0f, 1.0f }));
}

TEST_F(TestAabb, InvertedBoxIsEmpty)
{
	AabbF box { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } };
	EXPECT_TRUE(box.isEmpty());
	EXPECT_TRUE(box.extents().equalsEpsilon(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.halfSize().equalsEpsilon(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_FLOAT_EQ(box.radius(), 0.0f);
	EXPECT_FALSE(box.contains(Vector3F { 0.5f, 0.5f, 0.5f }));
}

TEST_F(TestAabb, FromPointsIteratorRange)
{
	const std::vector<Vector3F> points { { -1.0f, -2.0f, -3.0f },
										 { 4.0f, 5.0f, 6.0f },
										 { 0.0f, 0.0f, 0.0f } };
	AabbF box = AabbF::fromPoints(points.begin(), points.end());
	EXPECT_FALSE(box.isEmpty());
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { -1.0f, -2.0f, -3.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 4.0f, 5.0f, 6.0f }));
}

TEST_F(TestAabb, FromPointsSpan)
{
	const std::array<Vector3F, 2> points { Vector3F { 1.0f, 1.0f, 1.0f },
										   Vector3F { 2.0f, 3.0f, 4.0f } };
	AabbF box = AabbF::fromPoints(std::span<const Vector3F>(points));
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { 1.0f, 1.0f, 1.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 2.0f, 3.0f, 4.0f }));
}

TEST_F(TestAabb, FromPointsContiguousContainer)
{
	const std::vector<Vector3F> points { Vector3F { -2.0f, 0.0f, 0.0f },
										 Vector3F { 5.0f, 0.0f, 0.0f } };
	AabbF box = AabbF::fromPoints(points);
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { -2.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 5.0f, 0.0f, 0.0f }));
}

TEST_F(TestAabb, FromPointsSinglePointIsDegenerate)
{
	const std::vector<Vector3F> points { Vector3F { 3.0f, 3.0f, 3.0f } };
	AabbF box = AabbF::fromPoints(points.begin(), points.end());
	EXPECT_FALSE(box.isEmpty());
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { 3.0f, 3.0f, 3.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 3.0f, 3.0f, 3.0f }));
	EXPECT_FLOAT_EQ(box.radius(), 0.0f);
}

TEST_F(TestAabb, FromPointsEmptyRangeIsEmpty)
{
	const std::vector<Vector3F> points;
	AabbF box = AabbF::fromPoints(points.begin(), points.end());
	EXPECT_TRUE(box.isEmpty());
}

TEST_F(TestAabb, IncludePointGrowsBox)
{
	AabbF box;
	box.include(Vector3F { -1.0f, 0.0f, 0.0f });
	box.include(Vector3F { 2.0f, 3.0f, 4.0f });
	EXPECT_FALSE(box.isEmpty());
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { -1.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 2.0f, 3.0f, 4.0f }));
}

TEST_F(TestAabb, IncludePointInsideDoesNotShrink)
{
	AabbF box { { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 2.0f } };
	box.include(Vector3F { 1.0f, 1.0f, 1.0f });
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 2.0f, 2.0f, 2.0f }));
}

TEST_F(TestAabb, IncludeBoxGrowsToUnion)
{
	AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	const AabbF other { { -1.0f, -1.0f, -1.0f }, { 0.5f, 0.5f, 0.5f } };
	box.include(other);
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { -1.0f, -1.0f, -1.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 1.0f, 1.0f, 1.0f }));
}

TEST_F(TestAabb, IncludeBoxIntoEmptyAdoptsIt)
{
	AabbF box;
	const AabbF other { { -1.0f, -2.0f, -3.0f }, { 4.0f, 5.0f, 6.0f } };
	box.include(other);
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { -1.0f, -2.0f, -3.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 4.0f, 5.0f, 6.0f }));
}

TEST_F(TestAabb, IncludeEmptyBoxIsNoOp)
{
	AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	box.include(AabbF {});
	EXPECT_TRUE(box.getMin().equalsEpsilon(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.getMax().equalsEpsilon(Vector3F { 1.0f, 1.0f, 1.0f }));
}

TEST_F(TestAabb, DerivedQueries)
{
	AabbF box { { 0.0f, 0.0f, 0.0f }, { 2.0f, 4.0f, 6.0f } };
	EXPECT_TRUE(box.center().equalsEpsilon(Vector3F { 1.0f, 2.0f, 3.0f }));
	EXPECT_TRUE(box.extents().equalsEpsilon(Vector3F { 2.0f, 4.0f, 6.0f }));
	EXPECT_TRUE(box.halfSize().equalsEpsilon(Vector3F { 1.0f, 2.0f, 3.0f }));
	EXPECT_FLOAT_EQ(box.radius(), std::sqrt(1.0f + 4.0f + 9.0f));
}

TEST_F(TestAabb, CenterOfOffsetBox)
{
	const AabbF box { { 1.0f, 1.0f, 1.0f }, { 3.0f, 5.0f, 7.0f } };
	EXPECT_TRUE(box.center().equalsEpsilon(Vector3F { 2.0f, 3.0f, 4.0f }));
}

TEST_F(TestAabb, PositiveVertexSelectsFarthestCorner)
{
	const AabbF box { { -1.0f, -2.0f, -3.0f }, { 4.0f, 5.0f, 6.0f } };
	EXPECT_TRUE(box.positiveVertex(Vector3F { 1.0f, 1.0f, 1.0f })
					.equalsEpsilon(Vector3F { 4.0f, 5.0f, 6.0f }));
	EXPECT_TRUE(box.positiveVertex(Vector3F { -1.0f, -1.0f, -1.0f })
					.equalsEpsilon(Vector3F { -1.0f, -2.0f, -3.0f }));
	EXPECT_TRUE(box.positiveVertex(Vector3F { 1.0f, -1.0f, 1.0f })
					.equalsEpsilon(Vector3F { 4.0f, -2.0f, 6.0f }));
	EXPECT_TRUE(box.positiveVertex(Vector3F { 0.0f, 0.0f, 0.0f })
					.equalsEpsilon(Vector3F { 4.0f, 5.0f, 6.0f }));
}

TEST_F(TestAabb, ContainsBoundariesAndInterior)
{
	const AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	EXPECT_TRUE(box.contains(Vector3F { 0.5f, 0.5f, 0.5f }));
	EXPECT_TRUE(box.contains(Vector3F { 0.0f, 0.0f, 0.0f }));
	EXPECT_TRUE(box.contains(Vector3F { 1.0f, 1.0f, 1.0f }));
	EXPECT_FALSE(box.contains(Vector3F { 1.5f, 0.5f, 0.5f }));
	EXPECT_FALSE(box.contains(Vector3F { -0.01f, 0.5f, 0.5f }));
	EXPECT_FALSE(box.contains(Vector3F { 0.5f, 0.5f, 1.01f }));
	EXPECT_FALSE(AabbF {}.contains(Vector3F { 0.0f, 0.0f, 0.0f }));
}

TEST_F(TestAabb, IntersectsOverlappingTouchingAndDisjoint)
{
	const AabbF box { { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 2.0f } };
	const AabbF overlapping { { 1.0f, 1.0f, 1.0f }, { 3.0f, 3.0f, 3.0f } };
	const AabbF touching { { 2.0f, 2.0f, 2.0f }, { 4.0f, 4.0f, 4.0f } };
	const AabbF disjoint { { 3.0f, 3.0f, 3.0f }, { 4.0f, 4.0f, 4.0f } };
	const AabbF contained { { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f } };

	EXPECT_TRUE(box.intersects(overlapping));
	EXPECT_TRUE(overlapping.intersects(box));
	EXPECT_TRUE(box.intersects(touching));
	EXPECT_TRUE(box.intersects(box));
	EXPECT_TRUE(box.intersects(contained));
	EXPECT_FALSE(box.intersects(disjoint));
	EXPECT_FALSE(box.intersects(AabbF {}));
	EXPECT_FALSE(AabbF {}.intersects(box));
}

TEST_F(TestAabb, CenterDoesNotOverflowForHugeSameSignExtents)
{
	const float big = std::numeric_limits<float>::max();
	const AabbF box { { big, big, big }, { big, big, big } };
	EXPECT_FALSE(box.isEmpty());
	const Vector3F center = box.center();
	for (std::size_t i = 0; i < 3; ++i) {
		EXPECT_TRUE(std::isfinite(center[i]));
	}
}

TEST_F(TestAabb, CenterIsStableForHugeOppositeSignExtents)
{
	const float big = std::numeric_limits<float>::max();
	const AabbF box { { -big, -big, -big }, { big, big, big } };
	const Vector3F center = box.center();
	for (std::size_t i = 0; i < 3; ++i) {
		EXPECT_TRUE(std::isfinite(center[i]));
		EXPECT_FLOAT_EQ(center[i], 0.0f);
	}
}

TEST_F(TestAabb, DoublePrecisionSupported)
{
	const AabbD box { { 0.0, 0.0, 0.0 }, { 2.0, 4.0, 6.0 } };
	EXPECT_TRUE(box.center().equalsEpsilon(Vector3D { 1.0, 2.0, 3.0 }));
	EXPECT_DOUBLE_EQ(box.radius(), std::sqrt(14.0));
}

TEST_F(TestAabb, QueriesAreNoexcept)
{
	const AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	AabbF mutableBox;

	EXPECT_TRUE(noexcept(box.isEmpty()));
	EXPECT_TRUE(noexcept(box.getMin()));
	EXPECT_TRUE(noexcept(box.getMax()));
	EXPECT_TRUE(noexcept(box.center()));
	EXPECT_TRUE(noexcept(box.extents()));
	EXPECT_TRUE(noexcept(box.halfSize()));
	EXPECT_TRUE(noexcept(box.radius()));
	EXPECT_TRUE(noexcept(box.contains(box.getMax())));
	EXPECT_TRUE(noexcept(box.intersects(box)));
	EXPECT_TRUE(noexcept(box.positiveVertex(box.getMax())));
	EXPECT_TRUE(noexcept(mutableBox.include(box.getMax())));
	EXPECT_TRUE(noexcept(mutableBox.include(box)));
}

TEST_F(TestAabb, StreamInsertion)
{
	const AabbF box { { 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f, 3.0f } };
	std::ostringstream stream;
	stream << box;
	EXPECT_NE(stream.str().find("AabbF"), std::string::npos);
	EXPECT_NE(stream.str().find("min="), std::string::npos);
	EXPECT_NE(stream.str().find("max="), std::string::npos);
}
