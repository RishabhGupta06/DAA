#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Selection Sort function
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    // One by one move the boundary of the unsorted sub-array
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap the found minimum element with the first element
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

// Helper function to execute sort and measure time
void runAndMeasure(vector<int> data, string case_name, string complexity) {
    cout << "Running " << case_name << " (" << complexity << ")..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    selectionSort(data);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> execution_time = end_time - start_time;
    cout << "Execution Time : " << execution_time.count() << " ms\n\n";
}

int main() {
    // 10,000 elements. Selection Sort does exactly N(N-1)/2 comparisons every time.
    int data_size = 10000;
    
    // 1. BEST CASE: Already sorted array.
    // Unlike Bubble Sort, Selection Sort doesn't know it's sorted. It still 
    // scans the entire remaining array looking for a smaller element.
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
    // Takes the same number of comparisons as the Best Case, but performs
    // slightly more re-assignments of the 'min_idx' variable internally.
    vector<int> worst_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        worst_case_data[i] = data_size - i;
    }

    cout << "==========================================\n";
    cout << "  SELECTION SORT TIME COMPLEXITY BENCHMARK\n";
    cout << "  Array Size: " << data_size << " elements\n";
    cout << "==========================================\n\n";

    runAndMeasure(best_case_data, "Best Case Dataset", "O(n^2)");
    runAndMeasure(average_case_data, "Average Case Dataset", "O(n^2)");
    runAndMeasure(worst_case_data, "Worst Case Dataset", "O(n^2)");
    cout<<"Made by Rishabh Gupta";
    return 0;
}