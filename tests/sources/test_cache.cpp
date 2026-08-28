#include "test_cache.hpp"

#include "utility/cache.hpp"

using namespace utility;

namespace tests::utility
{

	TEST_F(TestCache, StartsEmpty)
	{
		Cache<int, int> cache;
		EXPECT_TRUE(cache.empty());
		EXPECT_EQ(cache.size(), 0);
	}

	TEST_F(TestCache, PutAndGet)
	{
		Cache<std::string, int> cache;
		cache.put("answer", 42);
		EXPECT_TRUE(cache.contains("answer"));
		EXPECT_EQ(cache.get("answer"), std::optional<int>(42));
	}

	TEST_F(TestCache, GetMissingReturnsNullopt)
	{
		Cache<int, int> cache;
		EXPECT_EQ(cache.get(1), std::nullopt);
		EXPECT_FALSE(cache.contains(1));
	}

	TEST_F(TestCache, PutOverwrites)
	{
		Cache<int, int> cache;
		cache.put(1, 10);
		cache.put(1, 20);
		EXPECT_EQ(cache.get(1), std::optional<int>(20));
	}

	TEST_F(TestCache, PutMove)
	{
		Cache<int, std::string> cache;
		std::string value = "hello";
		cache.put(1, std::move(value));
		EXPECT_EQ(cache.get(1), std::optional<std::string>("hello"));
	}

	TEST_F(TestCache, EmplaceReturnsEntry)
	{
		Cache<int, std::string> cache;
		std::string &entry = cache.emplace(1, "alpha");
		EXPECT_EQ(entry, "alpha");
		EXPECT_TRUE(cache.contains(1));
	}

	TEST_F(TestCache, EraseExistingReturnsTrue)
	{
		Cache<int, int> cache;
		cache.put(1, 1);
		EXPECT_TRUE(cache.erase(1));
		EXPECT_FALSE(cache.contains(1));
	}

	TEST_F(TestCache, EraseMissingReturnsFalse)
	{
		Cache<int, int> cache;
		EXPECT_FALSE(cache.erase(42));
	}

	TEST_F(TestCache, EraseIfRemovesMatching)
	{
		Cache<int, int> cache;
		cache.put(1, 5);
		cache.put(2, 15);
		cache.put(3, 25);
		cache.erase_if([](int, int value) { return value > 10; });
		EXPECT_TRUE(cache.contains(1));
		EXPECT_FALSE(cache.contains(2));
		EXPECT_FALSE(cache.contains(3));
	}

	TEST_F(TestCache, ApplyMutatesEntries)
	{
		Cache<int, int> cache;
		cache.put(1, 1);
		cache.put(2, 2);
		cache.apply([](int, int &value) { value *= 2; });
		EXPECT_EQ(cache.get(1), std::optional<int>(2));
		EXPECT_EQ(cache.get(2), std::optional<int>(4));
	}

	TEST_F(TestCache, ClearEmptiesCache)
	{
		Cache<int, int> cache;
		cache.put(1, 1);
		cache.put(2, 2);
		cache.clear();
		EXPECT_TRUE(cache.empty());
	}

}	 // namespace tests::utility
