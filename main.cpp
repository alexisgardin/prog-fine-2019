#include <benchmark/benchmark.h>
#include <iostream>
#include <ctime>


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


BENCHMARK_MAIN();

/**
int main() {
    unsigned long x = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned long i = 0; i < 1000000; i++) {
        x += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds =
            std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(
                    end - start);
    std::cout << elapsed_seconds.count() / 1000000 << std::endl;
    std::cout << x << std::endl;
}**/