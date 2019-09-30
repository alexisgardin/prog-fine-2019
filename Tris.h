//
// Created by Alexis Gardin on 2019-09-23.
//

#ifndef PROGFINE_TRIS_H
#define PROGFINE_TRIS_H

#include <iostream>
#include <vector>
#include <functional>

/**
 * Sorts to implement:
 *  - Selection
 *  - Insertion
 *  - Merge
 *  - Heap
 *  - Quick
 *  - Counting
 *  - Native
 *  - Smooth
 */

struct myclass {
    bool operator()(int i, int j) { return (i < j); }
} myobject;

namespace Tris {

    using namespace std;

    void print_array(int arr[], int N) {
        for (int i = 0; i < N; ++i) {
            std::cout << arr[i] << ", ";
        }
        std::cout << std::endl;
    }

    /**********************************
     *         Selection Sort         *
     **********************************/
    void selectionSort(int tab[], int N) {
        int i, j, s, temp;
        for (i = 0; i < N - 1; i++) {
            s = i;
            for (j = i + 1; j < N; j++) {
                if (tab[j] < tab[s])
                    s = j;
            }
            temp = tab[i];
            tab[i] = tab[s];
            tab[s] = temp;
        }
    }

    /**********************************
     *         Insertion Sort         *
     **********************************/
    void insertionSort(int tab[], int N) {
        int i, j, temp;
        for (i = 1; i < N; i++) {
            j = i;
            while (j > 0 && tab[j - 1] > tab[j]) {
                temp = tab[j];
                tab[j] = tab[j - 1];
                tab[j - 1] = temp;
                j--;
            }
        }
    }

    /**********************************
     *          Merge Sort            *
     **********************************/
    void Merge(int A[], int p, int q, int r) {

        int n1, n2, i, j, k;
        //size of left array=n1
        //size of right array=n2
        n1 = q - p + 1;
        n2 = r - q;

        int *L = new int[n1];
        int *R = new int[n2];
        //initializing the value of Left part to L[]
        for (i = 0; i < n1; i++) {
            L[i] = A[p + i];
        }
        //initializing the value of Right Part to R[]
        for (j = 0; j < n2; j++) {
            R[j] = A[q + j + 1];
        }
        i = 0, j = 0;
        //Comparing and merging them
        //into new array in sorted order
        for (k = p; i < n1 && j < n2; k++) {
            if (L[i] < R[j]) {
                A[k] = L[i++];
            } else {
                A[k] = R[j++];
            }
        }
        //If Left Array L[] has more elements than Right Array R[]
        //then it will put all the
        // reamining elements of L[] into A[]
        while (i < n1) {
            A[k++] = L[i++];
        }
        //If Right Array R[] has more elements than Left Array L[]
        //then it will put all the
        // reamining elements of L[] into A[]
        while (j < n2) {
            A[k++] = R[j++];
        }

        delete[] L;
        delete[] R;
    }

    //This is Divide Part
    //This part will Divide the array into
    //Sub array and then will Merge them
    //by calling Merge()
    void MergeSort(int A[], int p, int r) {
        int q;
        if (p < r) {
            q = (p + r) / 2;
            MergeSort(A, p, q);
            MergeSort(A, q + 1, r);
            Merge(A, p, q, r);
        }
    }

    void mergeSort(int tab[], int N) {
        MergeSort(tab, 0, N - 1);
    }

    /**********************************
     *          Heap Sort             *
     **********************************/
    // To heapify a subtree rooted with node i which is
    // an index in arr[]. n is size of heap
    void heapify(int arr[], int n, int i) {
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l] > arr[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && arr[r] > arr[largest])
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    void heapSort(int arr[], int n) {
        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // One by one extract an element from heap
        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            swap(arr[0], arr[i]);

            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    /**********************************
     *          Quick Sort            *
     **********************************/
    void quick(int *array, int low, int high) {
        int i = low;
        int j = high;
        int pivot = array[(i + j) / 2];
        int temp;

        while (i <= j) {
            while (array[i] < pivot)
                i++;
            while (array[j] > pivot)
                j--;
            if (i <= j) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
        if (j > low)
            quick(array, low, j);
        if (i < high)
            quick(array, i, high);
    }

    void quickSort(int tab[], int N) {
        quick(tab, 0, N - 1);
    }

    /**********************************
     *         Counting Sort          *
     **********************************/
    void countingSort(int tab[], int N) {
        vector<int> arr(tab, tab + N);
        int max = *max_element(arr.begin(), arr.end());
        int min = *min_element(arr.begin(), arr.end());
        int range = max - min + 1;

        vector<int> count(range), output(arr.size());
        for (int i : arr)
            count[i - min]++;

        for (int i = 1; i < count.size(); i++)
            count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - min] - 1] = arr[i];
            count[arr[i] - min]--;
        }

        for (int i = 0; i < arr.size(); i++)
            arr[i] = output[i];

        std::copy(arr.begin(), arr.end(), tab);
    }

    /**********************************
     *          Native Sort           *
     **********************************/
    void nativeSort(int tab[], int N) {
        vector<int> arr(tab, tab + N);
        std::sort(arr.begin(), arr.end(), myobject);
        std::copy(arr.begin(), arr.end(), tab);
    }
}


#endif //PROGFINE_TRIS_H
