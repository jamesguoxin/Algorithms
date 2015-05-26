//
//  heap_min.h
//  maintain_median
//
//  Created by Xin Guo on 11/05/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#ifndef maintain_median_heap_min_h
#define maintain_median_heap_min_h

#include <vector>

class heap_min {
public:
    std::vector<int> heap_array;
    
    int Extract_Min();
    int Min_Value();
    int heap_size();
    void Insert(int key);
    void Bubble_Up(int position);
    void Bubble_Down(int position);
};


#endif
