//
//  main.cpp
//  dijkstra
//
//  Created by Xin Guo on 31/12/14.
//  Copyright (c) 2014 JamesGuo. All rights reserved.
//

#include <iostream>
#include <climits>
#include <vector>
#include <map>

const int PLUS_INFINITY = INT_MAX;

class element {
public:
    int node;
    int key;
    
    void setElements(int node_v, int key_v) {
        node = node_v;
        key = key_v;
    }
};

class node_heap {
public:
    std::vector<int> heap;
    std::map<int, int> position;
    int tracker;
    
    node_heap(int nbV) {
        heap.assign(nbV, PLUS_INFINITY);
        
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
