#include <benchmark/benchmark.h>
#include <cstdlib>

extern "C" {
#include "list.h"
}

#include "bench_helpers.h"

static void bm_list_copy(benchmark::State& state) {
  List list = {};
  add_links(&list, state.range(0));
  assign_refs(&list);
  for (auto _ : state) {
    List copy = {};
    list_copy(&list, &copy);
  }
  list_free(&list);
}
BENCHMARK(bm_list_copy)->Range(8, 8<<10)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
