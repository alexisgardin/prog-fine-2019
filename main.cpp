#include <benchmark/benchmark.h>
#include <iostream>
#include <ctime>
#include "Tris.h"
#include "Generator.h"
#include <functional>

#define RANGE_MAX 1000000

using namespace std;

typedef std::function<void(int [], int)> TrisF;

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
BENCHMARK_CAPTURE(BM_TRIS, BM_SELECTIONSORT_RANDOM, Tris::selectionSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_SELECTIONSORT_ORDERED, Tris::selectionSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_SELECTIONSORT_INVERSE, Tris::selectionSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_INSERTIONSORT_RANDOM, Tris::insertionSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_INSERTIONSORT_ORDERED, Tris::insertionSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_INSERTIONSORT_INVERSE, Tris::insertionSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_MERGESORT_RANDOM, Tris::mergeSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_MERGESORT_ORDERED, Tris::mergeSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_MERGESORT_INVERSE, Tris::mergeSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_HEAPSORT_RANDOM, Tris::heapSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_HEAPSORT_ORDERED, Tris::heapSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_HEAPSORT_INVERSE, Tris::heapSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_QUICKSORT_RANDOM, Tris::quickSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_QUICKSORT_ORDERED, Tris::quickSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_QUICKSORT_INVERSE, Tris::quickSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_COUNTINGSORT_RANDOM, Tris::countingSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_COUNTINGSORT_ORDERED, Tris::countingSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_COUNTINGSORT_INVERSE, Tris::countingSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);


BENCHMARK_CAPTURE(BM_TRIS, BM_NATIVESORT_RANDOM, Tris::nativeSort, false, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_NATIVESORT_ORDERED, Tris::nativeSort, true, false)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);
BENCHMARK_CAPTURE(BM_TRIS, BM_NATIVESORT_INVERSE, Tris::nativeSort, false, true)->Unit(
        benchmark::kMillisecond)->RangeMultiplier(2)->Range(1,
                                                            RANGE_MAX);

BENCHMARK_MAIN();

void testSort(std::string sortName, std::function<void(int [], int)> func, std::vector<int> list) {
    int arr[list.size()];
    std::copy(list.begin(), list.end(), arr);

    Tris::cout << sortName << "(Not sorted): \t";
    Tris::print_array(arr, list.size());

    func(arr, list.size());

    Tris::cout << sortName << ": \t\t\t\t";
    Tris::print_array(arr, list.size());
    Tris::cout << Tris::endl;
}

/*
int main() {
    std::vector<int> list = Generator::randomList(0, 100, 12);
    testSort("Selection Sort", Tris::selectionSort, list);
    testSort("Insertion Sort", Tris::insertionSort, list);
    testSort("Merge Sort", Tris::mergeSort, list);
    testSort("Heap Sort", Tris::insertionSort, list);
    testSort("Quick Sort", Tris::insertionSort, list);
    testSort("Counting Sort", Tris::countingSort, list);
    testSort("Native Sort", Tris::nativeSort, list);
}
*/
