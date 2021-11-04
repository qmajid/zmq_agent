#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>
#include "hello.h"

// static void BM_StringCreation(benchmark::State& state) {
//   for (auto _ : state)
//     std::string empty_string;
// }
// // Register the function as a benchmark
// BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

static void BM_RandomNumber(benchmark::State& state){
  Test t;
  for (auto _ : state)
  {
      t.hello_google_benchmark(state.range(0));
  }
}
BENCHMARK(BM_RandomNumber)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

static void accumlate_bench(benchmark::State& state){
  // 2^10
  //auto N = 1 << 10;
  auto N = 1 << state.range(0);

  std::vector<int> v(N);
  std::generate(begin(v), end(v), []{return rand() % 100; });

  int result = 0;

  for (auto _ : state){
    result = std::accumulate(begin(v), end(v), 0);
  }
}
BENCHMARK(accumlate_bench)->DenseRange(10, 14, 1);
BENCHMARK(accumlate_bench)->DenseRange(10, 14, 1)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();