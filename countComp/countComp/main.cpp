//
//  main.cpp
//  countComp
//
//  Created by Xin Guo on 01/11/14.
//  Copyright (c) 2014 JamesGuo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
unsigned long long int nbComp = 0;

int quicksort1(int* IntegerArray, int start, int end) {
    nbComp = nbComp + end - start;
    if (start >= end) {
        return start;
    }
    int pivot = IntegerArray[start];
    int position;
    int tmp, l_i, r_i;
    int left, right;
    
    l_i = start;
    
    for (r_i = start; r_i < end; r_i++) {
        if (IntegerArray[r_i + 1] < pivot) {
            tmp = IntegerArray[l_i + 1];
            IntegerArray[l_i + 1] = IntegerArray[r_i + 1];
            IntegerArray[r_i + 1] = tmp;
            l_i = l_i + 1;
        }
    }
    tmp = pivot;
    IntegerArray[start] = IntegerArray[l_i];
    IntegerArray[l_i] = tmp;
    left = quicksort1(IntegerArray, start, l_i - 1);
    right = quicksort1(IntegerArray, l_i + 1, end);
    position = l_i;
    return position;
}

int quicksort2(int* IntegerArray, int start, int end) {
    nbComp = nbComp + end - start;
    if (start >= end) {
        return start;
    }
    int pivot = IntegerArray[end];
    IntegerArray[end] = IntegerArray[start];
    IntegerArray[start] = pivot;
    int position;
    int tmp, l_i, r_i;
    int left, right;
    
    l_i = start;
    
    for (r_i = start; r_i < end; r_i++) {
        if (IntegerArray[r_i + 1] < pivot) {
            tmp = IntegerArray[l_i + 1];
            IntegerArray[l_i + 1] = IntegerArray[r_i + 1];
            IntegerArray[r_i + 1] = tmp;
            l_i = l_i + 1;
        }
    }
    tmp = pivot;
    IntegerArray[start] = IntegerArray[l_i];
    IntegerArray[l_i] = tmp;
    left = quicksort2(IntegerArray, start, l_i - 1);
    right = quicksort2(IntegerArray, l_i + 1, end);
    position = l_i;
    return position;
}

int quicksort3(int* IntegerArray, int start, int end) {
    nbComp = nbComp + end - start;
    int pivot = 0;
    int tmp;
    if (start >= end) {
        return start;
    } else if (end - start == 1) {
        if (IntegerArray[start] > IntegerArray[end]) {
            tmp = IntegerArray[start];
            IntegerArray[start] = IntegerArray[end];
            IntegerArray[end] = tmp;
        }
        return start;
    }
    int first = IntegerArray[start];
    int second, se_posi;
    int third = IntegerArray[end];
    if ((end - start + 1) % 2 == 1) {
        se_posi = start + (end - start) / 2;
        second = IntegerArray[se_posi];
    } else {
        se_posi = start + (end - start - 1) / 2;
        second = IntegerArray[se_posi];
    }
    if ((first < second && first > third) || (first < third && first > second)) {
        pivot = first;
    } else if ((second < first && second > third) || (second < third && second > first)) {
        pivot = second;
        tmp = IntegerArray[start];
        IntegerArray[start] = pivot;
        IntegerArray[se_posi] = tmp;
    } else if ((third < first && third > second) || (third < second && third > first)) {
        pivot = third;
        tmp = IntegerArray[start];
        IntegerArray[start] = pivot;
        IntegerArray[end] = tmp;
    }
    int position;
    int l_i, r_i;
    int left, right;
    
    l_i = start;
    
    for (r_i = start; r_i < end; r_i++) {
        if (IntegerArray[r_i + 1] < pivot) {
            tmp = IntegerArray[l_i + 1];
            IntegerArray[l_i + 1] = IntegerArray[r_i + 1];
            IntegerArray[r_i + 1] = tmp;
            l_i = l_i + 1;
        }
    }
    tmp = pivot;
    IntegerArray[start] = IntegerArray[l_i];
    IntegerArray[l_i] = tmp;
    left = quicksort3(IntegerArray, start, l_i - 1);
    right = quicksort3(IntegerArray, l_i + 1, end);
    position = l_i;
    return position;
}

unsigned long long int countComp(int* IntegerArray, int start, int end) {
    int position;
    position = quicksort1(IntegerArray, start, end);
    return nbComp;
}

int main(int argc, const char * argv [] ) {
    std::ifstream file("/Users/JamesGuo/git_master/Algorithms/QuickSort.txt");
    std::string str;
    int IntegerArray[10000];
    int value;
    int i;
    unsigned long long int result;
    while (std::getline(file, str)) {
        value = atoi(str.c_str());
        IntegerArray[i] = value;
        i++;
    }
    result = countComp(IntegerArray, 0, 9999);
    std::cout << result << std::endl;
    return 0;
}
