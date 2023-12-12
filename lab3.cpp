#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

void bubble_sort(std::vector<int>& arr, Stats& statistics) {
    size_t n = arr.size();
    statistics.comparison_count = 0;
    statistics.copy_count = 0;
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            ++statistics.comparison_count;
            if (arr[j] > arr[j + 1]) {
                ++statistics.copy_count;
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubble_sort_fixed(int* start, int* end, Stats& statistics) {
    statistics.comparison_count = 0;
    statistics.copy_count = 0;
    for (int *i = start; i < end; i++) {
        for (int* j = start; j < end - (i - start) - 1; j++) {
            ++statistics.comparison_count;
            if (*(j + 1) < *j) {
                swap(*(j + 1), *j);
                ++statistics.copy_count;
            }
        }
    }
}

int partition(std::vector<int>& arr, int begin, int end, Stats& statistics)
{
    if (arr.size() <= 1)
        return 0;

    int temp = arr[end];
    int index = begin;
    for (int j = begin; j < end; j++)
    {
        ++statistics.comparison_count;
        if (arr[j] < temp)
        {
            ++statistics.copy_count;
            swap(arr[index], arr[j]);
            ++index;
        }
    }
    ++statistics.copy_count;
    swap(arr[index], arr[end]);
    return index;
}

void quick_sort(std::vector<int>& arr, int begin, int end, Stats& statistics)
{
    if (arr.size() <= 1)
        return;

    if (begin < end)
    {
        int tmp = partition(arr, begin, end, statistics);
        quick_sort(arr, begin, tmp - 1, statistics);
        quick_sort(arr, tmp + 1, end, statistics);
    }
}



void heapify(std::vector<int>& arr, int N, int i, Stats& statistics)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < N)
    {
        ++statistics.comparison_count;
        if (arr[l] > arr[largest])
            largest = l;
    }
    if (r < N)
    {
        ++statistics.comparison_count;
        if (arr[r] > arr[largest])
            largest = r;
    }
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        ++statistics.copy_count;
        heapify(arr, N, largest, statistics);
    }
}

void heap_sort(std::vector<int>& arr, int N, Stats& statistics)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i, statistics);

    for (int i = N - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        ++statistics.copy_count;
        heapify(arr, i, 0, statistics);
    }
}


Stats count(std::vector<int> arr, int experiments) {
    Stats total_stats;
    for (int i = 0; i < experiments; ++i) {
        std::vector<int> temp_arr = arr;
        int size = temp_arr.size();
        Stats current_stats;
        current_stats.comparison_count = 0;
        current_stats.copy_count = 0;

        //bubble_sort(temp_arr, current_stats);
        //bubble_sort_fixed(&arr[0], &arr[0] + arr.size(), current_stats);
        quick_sort(temp_arr, 0, size-1, current_stats);
        //heap_sort(temp_arr, size - 1, current_stats);
        total_stats.comparison_count += current_stats.comparison_count;
        total_stats.copy_count += current_stats.copy_count;
    }
    total_stats.comparison_count /= experiments;
    total_stats.copy_count /= experiments;
    return total_stats;
}

void print(const Stats& stats,int i) {
    std::cout << "Comparison Count: " << stats.comparison_count
        << ", Copy Count: " << stats.copy_count << std::endl;
}

int main() {
    const int num_experiments = 100;
    std::vector<int> sorted_arr, reverse_arr, random_arr;
    for (int i = 1000; i <= 10000; i+=1000) {
        sorted_arr.clear();
        reverse_arr.clear();
        random_arr.clear();
        for (int j = 1; j <= i; ++j) {
            sorted_arr.push_back(j);
            reverse_arr.push_back(i - j + 1);
            random_arr.push_back(rand() % i + 1);
        }
        Stats random_stats = count(random_arr, num_experiments);
        cout<<"Random Array (" << i << " elements):" ;
        print(random_stats, i);
        Stats sorted_stats = count(sorted_arr, 1);
        cout << "Sorted Array (" << i << " elements):";
        print(sorted_stats, i);
        Stats reverse_stats = count(reverse_arr, 1);
        cout << "Reverse Array (" << i << " elements):";
        print(reverse_stats, i);
        std::cout << std::endl;
    }
    return 0;
}







