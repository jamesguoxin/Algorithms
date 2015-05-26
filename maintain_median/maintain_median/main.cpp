//
//  main.cpp
//  maintain_median
//
//  Created by Xin Guo on 11/05/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "heap_min.h"
#include "heap_max.h"

class median {
public:
    int med;
    int number;
    heap_min min_heap;
    heap_max max_heap;
    
    median() {
        number = 0;
    }
    
    int Extract_Med() {
        return med;
    }
    
    void Add_Int(int value) {
        if (number == 0) {
            med = value;
            number++;
        } else if (number == 1) {
            if (value < med) {
                min_heap.Insert(med);
                max_heap.Insert(value);
                med = value;
                number++;
            } else {
                min_heap.Insert(value);
                max_heap.Insert(med);
                number++;
            }
        } else if (min_heap.heap_size() == max_heap.heap_size()) {
            if (value < max_heap.Max_Value()) {
                max_heap.Insert(value);
                med = max_heap.Max_Value();
                number++;
            } else if (value > min_heap.Min_Value()) {
                min_heap.Insert(value);
                med = min_heap.Min_Value();
                number++;
            } else {
                max_heap.Insert(value);
                med = value;
                number++;
            }
            
        } else if (min_heap.heap_size() == max_heap.heap_size() - 1) {
            if (value < max_heap.Max_Value()) {
                max_heap.Insert(value);
                int max_value = max_heap.Extract_Max();
                min_heap.Insert(max_value);
                med = max_heap.Max_Value();
                number++;
            } else {
                min_heap.Insert(value);
                med = max_heap.Max_Value();
                number++;
            }
        } else if (min_heap.heap_size() == max_heap.heap_size() + 1) {
            if (value > min_heap.Min_Value()) {
                min_heap.Insert(value);
                int min_value = min_heap.Extract_Min();
                max_heap.Insert(min_value);
                med = max_heap.Max_Value();
                number++;
            } else {
                max_heap.Insert(value);
                med = max_heap.Max_Value();
                number++;
            }
        }
        
    }
    
};

int main(int argc, const char * argv[]) {
    std::string path = "/Users/JamesGuo/git_master/Algorithms/Median.txt";
    std::ifstream file(path);
    std::string str;
    median median_stream;
    int med_sum = 0;
    
    while (getline(file, str)) {
        int value = atoi(str.c_str());
        median_stream.Add_Int(value);
        int med = median_stream.Extract_Med();
        med_sum = (med_sum + med) % 10000;
    }
    std::cout << "The result is " << med_sum << std::endl;
    return 0;
}
