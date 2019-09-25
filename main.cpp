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
template<typename T, std::size_t N>
void print_array(const T(&a)[N], std::ostream &o = std::cout) {
    o << "{";
    for (std::size_t i = 0; i < N - 1; ++i) {
        o << a[i] << ", ";
    }
    o << a[N - 1] << "}\n";
}

int main() {

    std::vector<int> random = Generator::randomList(0, 100, 5);
    int arr[random.size()];
    std::copy(random.begin(), random.end(), arr);
    Tris::MergeSort(arr, 0, (int) random.size() - 1);
    std::cout << arr << std::endl;
}

