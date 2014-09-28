// Copyright 2014, James Guo
#include <fstream>
#include <string>
#include <cstdio>

// to use const whenever you could
unsigned long long int merge(int array[], const int low, const int mid, const int high) {
    int* tmp = new int[high + 1 - low];
    int left_start, left_end, right_start, right_end;
    int i, k;
    unsigned long long int nb_inversion_merge;
    
    left_start = low;
    left_end = mid;
    right_start = mid + 1;
    right_end = high;
    
    i = 0;
    nb_inversion_merge = 0;
    
    while ((left_start <= left_end) && (right_start <= right_end)) {
        // Here array[left_start] <= array[right_start] matters since we put left side as priority, then left_start > left_right will occur first
        if (array[left_start] <= array[right_start]) {
            tmp[i] = array[left_start];
            i++;
            left_start++;
        } else {
            tmp[i] = array[right_start];
            nb_inversion_merge = nb_inversion_merge + (left_end - left_start + 1);
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
    
    return nb_inversion_merge;
}
// Basic idea: number of inversions of an array is equal to the sum of the number of inversions of left sub-array, right sub-array and number of inversions between these two sub-arrays. Sorting on both sub-arrays won't change the number of inversions between the two sub-arrays
unsigned long long int number_inversions(int array[], const int low, const int high) {
    int mid;
    unsigned long long int nb_inver, nb_inver_l, nb_inver_r, nb_inver_m;
    
    mid = (high - low) / 2 + low;
    nb_inver = 0;
    // if low == high, it's the base case, we do nothing to array
    if (low < high) {
        nb_inver_l = number_inversions(array, low, mid);
        nb_inver_r = number_inversions(array, mid + 1, high);
        nb_inver_m = merge(array, low, mid, high);
        nb_inver = nb_inver_l + nb_inver_r + nb_inver_m;
    }
    
    return nb_inver;
}

int main() {
    std::ifstream file("/Users/JamesGuo/git_master/Algorithms/IntegerArray.txt");
    std::string str;
    int IntegerArray[100000];
    int value;
    int i = 0;
    unsigned long long int nb_inversion;
    while (std::getline(file, str)) {
        value = atoi(str.c_str());
        IntegerArray[i] = value;
        i++;
    }
    nb_inversion = number_inversions(IntegerArray, 0, 99999);
    printf("%llu\n", nb_inversion);
    return 0;
}

