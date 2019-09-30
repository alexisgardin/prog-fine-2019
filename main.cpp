
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
          std::ofstream &myfile) {
    std::vector<int> v = Generator::randomList(0, 100000, occurence);
    myfile << sortName << ",";
    if (isInOrder) {

        myfile << "ORDERED" << ",";
        sort(v.begin(), v.end(), greater<int>());

    } else if (isInverse) {
        myfile << "INVERSE" << ",";
        sort(v.begin(), v.end(), less<int>());
    } else {
        myfile << "RANDOM" << ",";
    }
    myfile << v.size() << ",";
    int arr[v.size()];

    std::copy(v.begin(), v.end(), arr);

    auto start = std::chrono::high_resolution_clock::now();
    func(arr, v.size());
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_seconds =
            std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                    end - start);


    myfile << elapsed_seconds.count() << "\n";
    std::cout << sortName << ", " << occurence << ", " << elapsed_seconds.count() << std::endl;
}

void runTest(std::string sortName, std::function<void(int [], int)> func, std::ofstream &myfile) {
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, false, false, i, myfile);
    }
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, true, false, i, myfile);
    }
    for (int i = 1; i < RANGE_MAX; i = i * 2) {
        benchSort(sortName, func, false, true, i, myfile);
    }
}

int main() {
    std::ofstream myfile;
    myfile.open("../benchmarkresult.csv");
    myfile << "tris, type, size, time\n";
    runTest("SELECTION_SORT", Tris::selectionSort, myfile);
    runTest("INSERTION_SORT", Tris::insertionSort, myfile);
    runTest("MERGE_SORT", Tris::mergeSort, myfile);
    runTest("COUNTING_SORT", Tris::countingSort, myfile);
    runTest("NATIVE_SORT", Tris::nativeSort, myfile);
    runTest("HEAP_SORT", Tris::heapSort, myfile);
    runTest("QUICK_SORT", Tris::quickSort, myfile);
    myfile.close();
}

