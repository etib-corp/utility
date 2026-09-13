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

#include <memory>
#include <atomic>
#include <cstddef>
#include <string>

#include <utility/cache.hpp>
#include <utility/logging/logger.hpp>
#include <utility/math/vector.hpp>
#include <utility/ressource_provider.hpp>
#include <utility/system_io/default_system_io.hpp>
#include <utility/system_io/file.hpp>

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
	void BM_RessourceProviderGetShaderID(benchmark::State &state)
	{
		utility::DefaultSystemIO systemIO;
		utility::RessourceProvider provider(systemIO);

		for (const std::string name: { "text", "mesh", "default" }) {
			provider.loadShaderFromAssets(
				std::make_shared<utility::File>(name + ".vs", "AAAA"),
				std::make_shared<utility::File>(name + ".fs", "AAAA"));
		}

		// Inflate the generic element-ID map with non-shader entries to show
		// the shader lookup is independent of the number of elements.
		for (int i = 0; i < state.range(0); ++i) {
			provider.loadCodePointsFromAsset(std::make_shared<utility::File>(
				"cp" + std::to_string(i) + ".codepoints", std::string()));
		}

		for (auto _: state) {
			benchmark::DoNotOptimize(provider.getShaderID("text"));
		}
	}

	BENCHMARK(BM_RessourceProviderGetShaderID)
		->Arg(0)
		->Arg(10)
		->Arg(100)
		->Arg(1000);
	// Counts emitted records without touching stdout so the benchmark measures
	// the logging path (level check, allocation, mutex, output) only.
	class CountingLogger: public utility::logging::Logger
	{
		public:
		std::atomic<std::size_t> emitted { 0 };

		CountingLogger(void)
			: Logger("Benchmark")
		{
		}

		void output(const utility::logging::LogRecord &) override
		{
			emitted.fetch_add(1, std::memory_order_relaxed);
		}
	};

	void BM_LoggerSuppressed(benchmark::State &state)
	{
		CountingLogger logger;
		logger.setMinLevel(utility::logging::LogLevel::WARNING_LEVEL);
		for (auto _: state) {
			for (int i = 0; i < state.range(0); ++i) {
				auto message = logger.debug();
				message << "entity " << i;
				auto *box = &message;
				benchmark::DoNotOptimize(box);
			}
		}
		state.counters["emitted"] =
			static_cast<double>(logger.emitted.load(std::memory_order_relaxed));
	}
	BENCHMARK(BM_LoggerSuppressed)->Arg(100)->Arg(1000);

	void BM_LoggerActive(benchmark::State &state)
	{
		CountingLogger logger;
		logger.setMinLevel(utility::logging::LogLevel::DEBUG_LEVEL);
		for (auto _: state) {
			for (int i = 0; i < state.range(0); ++i) {
				auto message = logger.debug();
				message << "entity " << i;
				auto *box = &message;
				benchmark::DoNotOptimize(box);
			}
		}
		state.counters["emitted"] =
			static_cast<double>(logger.emitted.load(std::memory_order_relaxed));
	}
	BENCHMARK(BM_LoggerActive)->Arg(100)->Arg(1000);

}	 // namespace

BENCHMARK_MAIN();
