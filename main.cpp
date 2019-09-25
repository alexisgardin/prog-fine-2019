#include <benchmark/benchmark.h>
#include <iostream>
#include <ctime>
#include "Tris.h"
#include "Generator.h"


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

BENCHMARK(BM_addition);

BENCHMARK(BM_addition_2);

BENCHMARK(BM_mutli);


//BENCHMARK_MAIN();


int main() {

    Tris::test();
    Generator::randomList(0, 100, 5);
}