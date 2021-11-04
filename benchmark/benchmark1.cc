#include <benchmark/benchmark.h>
#include "hello.h"

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

static void BM_RandomNumber(benchmark::State& state){
  Test t;
  int value = 100000;
  for (auto _ : state)
  {
      t.hello_google_benchmark(value);
  }
}
BENCHMARK(BM_RandomNumber);

BENCHMARK_MAIN();