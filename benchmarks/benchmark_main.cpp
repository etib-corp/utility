/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <benchmark/benchmark.h>

#include <string>

#include <utility/cache.hpp>
#include <utility/math/vector.hpp>

namespace
{

	void BM_Vector3FAdd(benchmark::State &state)
	{
		utility::math::Vector3F a { 1.0f, 2.0f, 3.0f };
		utility::math::Vector3F b { 4.0f, 5.0f, 6.0f };
		for (auto _: state) {
			auto c = a + b;
			benchmark::DoNotOptimize(c);
		}
	}
	BENCHMARK(BM_Vector3FAdd);

	void BM_Vector3FDot(benchmark::State &state)
	{
		utility::math::Vector3F a { 1.0f, 2.0f, 3.0f };
		utility::math::Vector3F b { 4.0f, 5.0f, 6.0f };
		for (auto _: state) {
			auto d = utility::math::dot(a, b);
			benchmark::DoNotOptimize(d);
		}
	}
	BENCHMARK(BM_Vector3FDot);

	void BM_CachePutGet(benchmark::State &state)
	{
		utility::Cache<std::string, int> cache;
		for (auto _: state) {
			for (int i = 0; i < state.range(0); ++i) {
				cache.put("key" + std::to_string(i), i);
			}
			state.PauseTiming();
			cache.clear();
			state.ResumeTiming();
		}
	}
	BENCHMARK(BM_CachePutGet)->Range(8, 8 << 10);

}	 // namespace

BENCHMARK_MAIN();
