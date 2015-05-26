//
//  heap_max.cpp
//  maintain_median
//
//  Created by Xin Guo on 26/05/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "heap_max.h"

int heap_max::Extract_Max() {
    int result = heap_array[0];
    std::iter_swap(heap_array.begin(), heap_array.begin() + heap_array.size() - 1);
    heap_array.pop_back();
    Bubble_Down(0);
    return result;
}

int heap_max::Max_Value() {
    return heap_array[0];
}

int heap_max::heap_size() {
    return int(heap_array.size());
}

void heap_max::Insert(int key) {
    heap_array.push_back(key);
    Bubble_Up(int(heap_array.size() - 1));
}

void heap_max::Bubble_Down(int position) {
    int left_child = position * 2 + 1;
    int right_child = position * 2 + 2;
    
    if (right_child <= (heap_array.size() - 1)) {
        if (heap_array[left_child] > heap_array[right_child] && heap_array[left_child] > heap_array[position]) {
            std::iter_swap(heap_array.begin() + position, heap_array.begin() + left_child);
            Bubble_Down(left_child);
        } else if (heap_array[right_child] > heap_array[left_child] && heap_array[right_child] > heap_array[position]) {
            std::iter_swap(heap_array.begin() + position, heap_array.begin() + right_child);
            Bubble_Down(right_child);
        }
    } else if (left_child <= (heap_array.size() - 1)) {
        if (heap_array[left_child] > heap_array[position]) {
            std::iter_swap(heap_array.begin() + position, heap_array.begin() + left_child);
            Bubble_Down(left_child);
        }
    }
    
}

void heap_max::Bubble_Up(int position) {
    int parent = (position - 1) / 2;
    
    if (heap_array[parent] < heap_array[position]) {
        std::iter_swap(heap_array.begin() + position, heap_array.begin() + parent);
        Bubble_Up(parent);
    }
    
}
