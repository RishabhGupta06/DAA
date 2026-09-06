#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Partition function using the Lomuto scheme
int partition(vector<int>& arr, int low, int high) {
    // Pick the middle element as the pivot and swap it to the end
    // This ensures an already sorted array triggers the O(n log n) Best Case
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);

    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort recursive function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper function to execute sort and measure time
void runAndMeasure(vector<int> data, string case_name, string complexity) {
    cout << "Running " << case_name << " (" << complexity << ")..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    quickSort(data, 0, data.size() - 1);
    auto end_time = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> execution_time = end_time - start_time;
    cout << "Execution Time : " << execution_time.count() << " ms\n\n";
}

int main() {
    // We use 10,000 elements. If we go too high (like 100,000), 
    // the Worst Case O(n^2) recursion depth will cause a Stack Overflow.
    int data_size = 10000;
    
    // 1. BEST CASE: Already sorted array. 
    // Because we pick the middle element as the pivot, it perfectly 
    // cuts the array 50/50 every single time.
    vector<int> best_case_data(data_size);
    for (int i = 0; i < data_size; i++) {
        best_case_data[i] = i; 
    }

    // 2. AVERAGE CASE: Randomly shuffled array.
    // The pivot roughly divides the array decently, maintaining logarithmic depth.
    vector<int> average_case_data(data_size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);
    for (int i = 0; i < data_size; i++) {
        average_case_data[i] = distrib(gen);
    }

    // 3. WORST CASE: Array of identical elements.
    // In the standard Lomuto partition scheme, if all elements are equal, 
    // they all get pushed to one side of the pivot. This creates a 
    // 0-to-(N-1) split every time, degrading performance to O(n^2).
    vector<int> worst_case_data(data_size, 7); 

    cout << "==========================================\n";
    cout << "   QUICK SORT TIME COMPLEXITY BENCHMARK   \n";
    cout << "   Array Size: " << data_size << " elements\n";
    cout << "==========================================\n\n";

    runAndMeasure(best_case_data, "Best Case Dataset", "O(n log n)");
    runAndMeasure(average_case_data, "Average Case Dataset", "O(n log n)");
    runAndMeasure(worst_case_data, "Worst Case Dataset", "O(n^2)");
    cout<<"Made by Rishabh Gupta"<<endl;

    return 0;
}