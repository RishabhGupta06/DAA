#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Optimized Bubble Sort function
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        // The last 'i' elements are already in place, so we don't check them
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no two elements were swapped in the inner loop, the array is sorted
        if (!swapped) {
            break;
        }
    }
}

// Helper function to execute sort and measure time
void runAndMeasure(vector<int> data, string case_name, string complexity) {
    cout << "Running " << case_name << " (" << complexity << ")..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    bubbleSort(data);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> execution_time = end_time - start_time;
    cout << "Execution Time : " << execution_time.count() << " ms\n\n";
}

int main() {
    // 10,000 elements. Bubble Sort's O(n^2) behavior will be very noticeable here.
    int data_size = 10000;
    
    // 1. BEST CASE: Already sorted array.
    // The optimized Bubble Sort makes exactly one pass (N comparisons), 
    // realizes no swaps were needed, and exits immediately.
    vector<int> best_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        best_case_data[i] = i; 
    }

    // 2. AVERAGE CASE: Randomly shuffled array.
    // Elements need to bubble up multiple times, requiring nested looping.
    vector<int> average_case_data(data_size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);
    for (int i = 0; i < data_size; i++) {
        average_case_data[i] = distrib(gen);
    }

    // 3. WORST CASE: Reverse sorted array.
    // Every single element must travel the maximum possible distance. 
    // Requires the maximum N^2/2 comparisons and N^2/2 swaps.
    vector<int> worst_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        worst_case_data[i] = data_size - i;
    }

    cout << "==========================================\n";
    cout << "   BUBBLE SORT TIME COMPLEXITY BENCHMARK  \n";
    cout << "   Array Size: " << data_size << " elements\n";
    cout << "==========================================\n\n";

    runAndMeasure(best_case_data, "Best Case Dataset", "O(n)");
    runAndMeasure(average_case_data, "Average Case Dataset", "O(n^2)");
    runAndMeasure(worst_case_data, "Worst Case Dataset", "O(n^2)");
    cout<<"Made by Rishabh Gupta";
    return 0;
}