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

}	 // namespace tests::utility
