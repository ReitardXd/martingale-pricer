#include <benchmark/benchmark.h>

static void placeholder_benchmark(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(state.iterations());
  }
}

BENCHMARK(placeholder_benchmark);
BENCHMARK_MAIN();
