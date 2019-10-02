
#include <iostream>
#include "Tris.h"
#include "Generator.h"
#include <functional>
#include <thread>
#include <fstream>

#define RANGE_MAX 1048577

using namespace std;

void
benchSort(std::string sortName, std::function<void(int [], int)> func, bool isInOrder, bool isInverse, int occurence,
          int iteration,
          std::ofstream &myfile) {

    std::vector<double> times;
    for (int i = 0; i < iteration; ++i) {
        std::vector<int> v = Generator::randomList(0, 100000, occurence);
        if (isInOrder) {
            sort(v.begin(), v.end(), greater<int>());

        } else if (isInverse) {

            sort(v.begin(), v.end(), less<int>());
        } else {
        }
        int arr[v.size()];

        std::copy(v.begin(), v.end(), arr);

        auto start = std::chrono::high_resolution_clock::now();
        func(arr, v.size());
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_seconds =
                std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                        end - start);
        times.push_back(elapsed_seconds.count());
    }
    myfile << sortName << ",";
    if (isInOrder) {
        myfile << "INVERSE" << ",";

    } else if (isInverse) {

        myfile << "ORDERED" << ",";
    } else {
        myfile << "RANDOM" << ",";
    }
    myfile << occurence << ",";
    double meanTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    myfile << meanTime << "\n";
    std::cout << sortName << ", " << occurence << ", " << meanTime << std::endl;
}

void runTest(std::string sortName, std::function<void(int [], int)> func, std::ofstream &myfile, int iteration) {
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, false, false, i, iteration, myfile);
    }
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, true, false, i, iteration, myfile);
    }
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, false, true, i, iteration, myfile);
    }
}

int main() {
    std::ofstream myfile;
    myfile.open("../benchmarkresult.csv");
    myfile << "tris,type,size,time\n";
    runTest("SELECTION_SORT", Tris::selectionSort, myfile, 3);
    runTest("INSERTION_SORT", Tris::insertionSort, myfile, 3);
    runTest("MERGE_SORT", Tris::mergeSort, myfile, 3);
    runTest("COUNTING_SORT", Tris::countingSort, myfile, 3);
    runTest("NATIVE_SORT", Tris::nativeSort, myfile, 3);
    runTest("HEAP_SORT", Tris::heapSort, myfile, 3);
    runTest("QUICK_SORT", Tris::quickSort, myfile, 3);
    myfile.close();
}

