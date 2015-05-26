//
//  heap_max.h
//  maintain_median
//
//  Created by Xin Guo on 26/05/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#ifndef maintain_median_heap_max_h
#define maintain_median_heap_max_h

class heap_max {
public:
    std::vector<int> heap_array;
    
    int Extract_Max();
    int Max_Value();
    int heap_size();
    void Insert(int key);
    void Bubble_Up(int position);
    void Bubble_Down(int position);
};

#endif
