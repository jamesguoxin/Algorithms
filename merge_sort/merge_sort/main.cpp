// Copyright 2014, James Guo
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>

// to use const whenever you could
void merge(int array[], const int low, const int mid, const int high) {
    int* tmp = new int[high + 1 - low];
    int left_start, left_end, right_start, right_end;
    int i, k;
    
    left_start = low;
    left_end = mid;
    right_start = mid + 1;
    right_end = high;
    
    i = 0;
    
    while ((left_start <= left_end) && (right_start <= right_end)) {
        // Here array[left_start] <= array[right_start] matters since we put left side as priority, then left_start > left_right will occur first
        if (array[left_start] <= array[right_start]) {
            tmp[i] = array[left_start];
            i++;
            left_start++;
        } else {
            tmp[i] = array[right_start];
            i++;
            right_start++;
        }
    }
    // See above why left_start > left_end
    if (left_start > left_end) {
        for (k = right_start; k <= right_end; k++) {
            tmp[i] = array[k];
            i++;
        }
    } else {
        for (k = left_start; k <= left_end; k++) {
            tmp[i] = array[k];
            i++;
        }
    }
    
    for (k = low; k <= high; k++) {
        array[k] = tmp[k - low];
        //printf("%d\n", array[k]);
    }
    
    delete[] tmp;
}

void merge_sort(int array[], const int low, const int high) {
    int mid;
    mid = (high - low) / 2 + low;
    
    // if low == high, it's the base case, we do nothing to array
    if (low < high) {
        merge_sort(array, low, mid);
        merge_sort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

int main() {
    std::ifstream file("/Users/JamesGuo/git_master/Algorithms/IntegerArray.txt");
    std::string str;
    int IntegerArray[100000];
    int value;
    int i = 0;
    while (std::getline(file, str)) {
        value = atoi(str.c_str());
        IntegerArray[i] = value;
        i++;
    }
    merge_sort(IntegerArray, 0, 99999);
    for (i = 0; i <= 100000; i++) {
        printf("%d\n", IntegerArray[i]);
    }
    return 0;
}

