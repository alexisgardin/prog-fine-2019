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
void print_array(int arr[], int N) {
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}


int main() {

    std::vector<int> random = Generator::randomList(0, 100, 5);
    int arr[random.size()];
    std::copy(random.begin(), random.end(), arr);
    Tris::MergeSort(arr, 0, (int) random.size() - 1);
    print_array(arr, random.size());
}

