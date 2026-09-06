#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Function to merge two sorted sub-arrays into one
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into arr
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// The main Merge Sort recursive function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return; // Base case: 1 or 0 elements
    }
    
    int mid = left + (right - left) / 2;

    // Recursively sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// Helper function to execute sort and measure time
void runAndMeasure(vector<int> data, string case_name, string complexity) {
    cout << "Running " << case_name << " (" << complexity << ")..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    mergeSort(data, 0, data.size() - 1);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> execution_time = end_time - start_time;
    cout << "Execution Time : " << execution_time.count() << " ms\n\n";
}

int main() {
    // Using 10,000 elements to perfectly match the Quick Sort test scale.
    // Notice that Merge Sort will NOT stack overflow on the worst case.
    int data_size = 10000;
    
    // 1. BEST CASE: Already sorted array.
    // Even though it's sorted, Merge Sort still recursively halves the array
    // and runs the merge loop. It just skips swapping elements across halves.
    vector<int> best_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        best_case_data[i] = i; 
    }

    // 2. AVERAGE CASE: Randomly shuffled array.
    vector<int> average_case_data(data_size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);
    for (int i = 0; i < data_size; i++) {
        average_case_data[i] = distrib(gen);
    }

    // 3. WORST CASE: Reverse sorted array.
    // Forces the merge step to constantly pull from the right array first,
    // maximizing the amount of structural "movement" during the merge.
    vector<int> worst_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        worst_case_data[i] = data_size - i;
    }

    cout << "==========================================\n";
    cout << "    MERGE SORT TIME COMPLEXITY BENCHMARK  \n";
    cout << "    Array Size: " << data_size << " elements\n";
    cout << "==========================================\n\n";

    runAndMeasure(best_case_data, "Best Case Dataset", "O(n log n)");
    runAndMeasure(average_case_data, "Average Case Dataset", "O(n log n)");
    runAndMeasure(worst_case_data, "Worst Case Dataset", "O(n log n)");
    cout<<"Made by Rishabh Gupta";
    return 0;
}