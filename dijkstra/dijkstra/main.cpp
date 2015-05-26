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
#include <fstream>
#include <algorithm>
using namespace std;

const int PLUS_INFINITY = 1000000;
const int SIZE = 200;

class heap_element {
public:
    int node;
    int key;       // key is the distance value
    
    heap_element(int node_v, int key_v) {
        node = node_v;
        key = key_v;
    }
};

class node_heap {
public:
    vector<heap_element> heap_;
    map<int, int> position;
    
    node_heap(int nb_vertices) {
        for (int i = 0; i < nb_vertices; i++) {
            heap_element node(i + 1, PLUS_INFINITY);
            heap_.push_back(node);
            if (position.find(i + 1) == position.end()) position[i + 1] = i;
        }
        
        heap_[0].key = 0;
    }
    
    heap_element extract_min() {
        // the first element is the node with smallest distance
        heap_element min_node(heap_[0].node, heap_[0].key);
        // first element will be deleted, the position needs to indicate that
        if (position.find(heap_[0].node) != position.end()) position[heap_[0].node] = PLUS_INFINITY;
        // swap last element and first element of heap_
        iter_swap(heap_.begin() + 0, heap_.begin() + heap_.size() - 1);
        position[heap_[0].node] = 0; // remember to update position each time
        // delete the original root of heap_
        heap_.pop_back();
        // bubble down the swapped root of heap_
        bubble_down(0);
        return min_node;
    }
    
    void decrease_key(int node, int new_key) {
        // the node is not deleted yet
        if (position[node] != PLUS_INFINITY) {
            // the new distance is smaller than stored distance
            if (heap_[position[node]].key > new_key) {
                heap_[position[node]].key = new_key;
                bubble_up(position[node]);
            }
        }
        
    }
    
    void bubble_up(unsigned int element_posi) {
        unsigned int parent_posi = (element_posi + 1) / 2 - 1;
        position[heap_[element_posi].node] = (int)element_posi;
        
        if ((heap_[parent_posi].key > heap_[element_posi].key) && parent_posi > 0) {
            iter_swap(heap_.begin() + element_posi, heap_.begin() + parent_posi);
            position[heap_[element_posi].node] = (int)element_posi;
            position[heap_[parent_posi].node] = (int)parent_posi;
            bubble_up(parent_posi);
        }
        
        if ((heap_[parent_posi].key > heap_[element_posi].key) && parent_posi == 0) {
            iter_swap(heap_.begin() + element_posi, heap_.begin() + parent_posi);
            position[heap_[element_posi].node] = (int)element_posi;
            position[heap_[parent_posi].node] = (int)parent_posi;
        }
    }
    
    void bubble_down(unsigned int element_posi) {
        unsigned int left_child_posi = 1 + 2 * element_posi;
        unsigned int right_child_posi = 2 + 2 * element_posi;
        position[heap_[(int)element_posi].node] = (int)element_posi;
        
        if (right_child_posi < heap_.size()) {
            if (heap_[left_child_posi].key < heap_[right_child_posi].key) {
                if (heap_[element_posi].key > heap_[left_child_posi].key) {
                    iter_swap(heap_.begin() + element_posi, heap_.begin() + left_child_posi);
                    position[heap_[element_posi].node] = (int)element_posi;
                    position[heap_[left_child_posi].node] = (int)left_child_posi;
                    bubble_down(left_child_posi);
                }
            } else {
                if (heap_[element_posi].key > heap_[right_child_posi].key) {
                    iter_swap(heap_.begin() + element_posi, heap_.begin() + right_child_posi);
                    position[heap_[element_posi].node] = (int)element_posi;
                    position[heap_[right_child_posi].node] = (int)right_child_posi;
                    bubble_down(right_child_posi);
                }
            }
        } else if (left_child_posi < heap_.size()) {
            if (heap_[element_posi].key > heap_[left_child_posi].key) {
                iter_swap(heap_.begin() + element_posi, heap_.begin() + left_child_posi);
                position[heap_[element_posi].node] = (int)element_posi;
                position[heap_[left_child_posi].node] = (int)left_child_posi;
                bubble_down(left_child_posi);
            }
        }
        
    }
};

map<int, int> dijkstra(map<int, map<int, int>> graph) {
    map<int, int> result;
    int extract_node;
    int new_node;
    int new_key;
    node_heap node_heap_(SIZE);
    while (node_heap_.heap_.size() != 0) {
        extract_node = node_heap_.heap_[0].node;
        if (graph.find(extract_node) != graph.end()) {
            for (auto it = graph[extract_node].begin(); it != graph[extract_node].end(); it++) {
                new_node = it->first;
                new_key = node_heap_.heap_[0].key + it->second;
                node_heap_.decrease_key(new_node, new_key);
            }

        }
        heap_element min_extracted = node_heap_.extract_min();
        //cout << "Extract Node is " << min_extracted.node << endl;
        //cout << "The minimum distance is " << min_extracted.key << endl;
        //cout << endl;
        //cout << node_heap_.position[80] << " : " << node_heap_.heap_[node_heap_.position[80]].node << " : " << node_heap_.heap_[node_heap_.position[80]].key << endl;
        //cout << endl;
        if (result.find(min_extracted.node) == result.end()) result[min_extracted.node] = min_extracted.key;
        
    }
    return result;
}

map<int, int> read_line(string line) {
    map<int, int> adjList;
    int desti;
    int length = 0;
    int count_tab = 0;
    int count_coma = 0;
    size_t index = 0;
    string integer;
    
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '\t' || line[i] == ',' || (i == line.size() - 1)) {
            if (line[i] == ',') {
                count_coma++;
                integer = line.substr(index, i - index);
                desti = atoi(integer.c_str());
                index = i + 1;
            }
            if (line[i] == '\t' || (i == line.size() - 1)) {
                count_tab++;
                if (i == line.size() - 1 && line[i] != '\t') {
                    integer = line.substr(index, i - index + 1);
                } else {
                    integer = line.substr(index, i - index);
                }
                length = atoi(integer.c_str());
                index = i + 1;
            }
            if (count_tab > 0 && count_tab == count_coma) {
                if (adjList.find(desti) == adjList.end()) {
                    adjList[desti] = length;
                }
            }
            
        }
    }
    return adjList;
}
map<int, map<int, int>> read_txt(string path) {
    map<int, map<int, int>> graph;
    ifstream file(path);
    string str;
    
    while (getline(file, str)) {
        int start;
        int count_tab = 0;
        size_t index = 0;
        string integer;
        map<int, int> adjList;
        
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] == '\t') {
                count_tab = count_tab + 1;
                
                if (count_tab == 1) {
                    integer = str.substr(index, i - index);
                    start = atoi(integer.c_str());
                    //cout << start << endl;
                    index = i + 1;
                    adjList = read_line(str.substr(index));
                    if (graph.find(start) == graph.end()) graph[start] = adjList;
                    break;
                }
            }
        }
        
    }
    
    return graph;
}

int main(int argc, const char * argv[]) {
    string txt_path = "/Users/JamesGuo/git_master/Algorithms/dijkstraData.txt";
    //string txt_path = "/Users/JamesGuo/git_master/Algorithms/dijTest2.txt";
    map<int, map<int, int>> graph;
    map<int, int> distance_result;
    graph = read_txt(txt_path);
    
    distance_result = dijkstra(graph);
    
    for (auto it = distance_result.begin(); it != distance_result.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
    return 0;
}
