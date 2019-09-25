#include <benchmark/benchmark.h>
#include <iostream>
#include <ctime>
#include "Tris.h"
#include "Generator.h"
#include <functional>

typedef std::function<void(int [], int)> TrisF;

using namespace std;

void print_array(int arr[], int N) {
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

static void BM_addition(benchmark::State &state) {

    unsigned long x = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x += 245);

    }
}

static void BM_addition_2(benchmark::State &state) {

    unsigned long x = 0;
    for (auto _ : state) {
        x += 245;

    }
}

static void BM_mutli(benchmark::State &state) {
    unsigned long x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x *= 2);
    }
}

/*
BENCHMARK(BM_addition);

BENCHMARK(BM_addition_2);

BENCHMARK(BM_mutli);*/


void benchmark_tris(std::function<void(int [], int)> tris, int array[], int N) {
    tris(array, N);
}

template<typename TrisF>
void BM_TRIS(benchmark::State &state, TrisF tris, bool isInOrder, bool isInverse) {

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> v = Generator::randomList(0, 100000, state.range(0));
        if (isInOrder) {
            sort(v.begin(), v.end(), greater<int>());
        } else if (isInverse) {

            sort(v.begin(), v.end(), less<int>());
        }
        int arr[v.size()];
        std::copy(v.begin(), v.end(), arr);
        state.ResumeTiming();
        benchmark_tris(tris, arr, v.size());

    }
}
// Registers a benchmark named "BM_takes_args/int_string_test" that passes
// the specified values to `extra_args`.
BENCHMARK_CAPTURE(BM_TRIS, BM_MERGE_SORT_RANDOM, Tris::launchMerge, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            1000000);
BENCHMARK_CAPTURE(BM_TRIS, BM_MERGE_SORT_ORDERED, Tris::launchMerge, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            1000000);
BENCHMARK_CAPTURE(BM_TRIS, BM_MERGE_SORT_INVERSE, Tris::launchMerge, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            1000000);

BENCHMARK_MAIN();



/*
int main() {

    print_array(arr, random.size());
}

*/