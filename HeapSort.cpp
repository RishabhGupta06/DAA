#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// To heapify a subtree rooted with node i, which is an index in arr[]. 
// n is size of the heap.
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;    // left child = 2*i + 1
    int right = 2 * i + 2;   // right child = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main Heap Sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Build a max heap
    // Start from the last non-leaf node and heapify all nodes in reverse order
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Step 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (the maximum element) to the end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Helper function to execute sort and measure time
void runAndMeasure(vector<int> data, string case_name, string complexity) {
    cout << "Running " << case_name << " (" << complexity << ")..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    heapSort(data);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> execution_time = end_time - start_time;
    cout << "Execution Time : " << execution_time.count() << " ms\n\n";
}

int main() {
    // 10,000 elements. Heap sort handles this effortlessly.
    int data_size = 10000;
    
    // 1. BEST CASE: All identical elements.
    // If all elements are equal, the heapify process does virtually no work 
    // because no swaps are needed when comparing identical values. 
    // (Note: A sorted array still requires work to build the Max-Heap).
    vector<int> best_case_data(data_size, 7);

    // 2. AVERAGE CASE: Randomly shuffled array.
    vector<int> average_case_data(data_size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);
    for (int i = 0; i < data_size; i++) {
        average_case_data[i] = distrib(gen);
    }

    // 3. WORST CASE: Reverse sorted (or completely sorted).
    // In both cases, the algorithm must do maximum work pulling the 
    // largest elements from the bottom of the tree up to the root.
    vector<int> worst_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        worst_case_data[i] = i; 
    }

    cout << "==========================================\n";
    cout << "     HEAP SORT TIME COMPLEXITY BENCHMARK  \n";
    cout << "     Array Size: " << data_size << " elements\n";
    cout << "==========================================\n\n";

    runAndMeasure(best_case_data, "Best Case Dataset", "O(n log n)");
    runAndMeasure(average_case_data, "Average Case Dataset", "O(n log n)");
    runAndMeasure(worst_case_data, "Worst Case Dataset", "O(n log n)");
    cout<<"Made by Rishabh Gupta";
    return 0;
}