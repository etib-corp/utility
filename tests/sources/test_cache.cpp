#include "test_cache.hpp"

#include <atomic>
#include <thread>
#include <vector>

#include "utility/cache.hpp"

using namespace utility;

namespace tests::utility
{

	TEST_F(TestCache, ConcurrentPutAndGet)
	{
		Cache<int, int> cache;
		constexpr int kThreads	= 8;
		constexpr int kPerThread = 200;

		std::vector<std::thread> writers;
		for (int t = 0; t < kThreads; ++t) {
			writers.emplace_back([&, t]() {
				for (int i = 0; i < kPerThread; ++i) {
					cache.put(t * kPerThread + i, i);
				}
			});
		}
		for (auto &thread: writers) {
			thread.join();
		}
		EXPECT_EQ(cache.size(), kThreads * kPerThread);
		EXPECT_EQ(cache.get(0), std::optional<int>(0));
	}

	TEST_F(TestCache, ConcurrentReadsDoNotCorrupt)
	{
		Cache<int, int> cache;
		for (int i = 0; i < 100; ++i) {
			cache.put(i, i);
		}

		std::atomic<int> successes { 0 };
		std::vector<std::thread> readers;
		for (int t = 0; t < 8; ++t) {
			readers.emplace_back([&]() {
				for (int i = 0; i < 100; ++i) {
					if (cache.get(i) == std::optional<int>(i)) {
						++successes;
					}
				}
			});
		}
		for (auto &thread: readers) {
			thread.join();
		}
		EXPECT_EQ(successes.load(), 800);
	}

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
