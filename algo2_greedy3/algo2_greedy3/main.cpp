//
//  main.cpp
//  algo2_greedy3
//
//  Created by Xin Guo on 31/07/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

class edge {
public:
    int node1;
    int node2;
    int edge_cost;
    
    edge () {
        node1 = 0;
        node2 = 0;
        edge_cost = 0;
    }
    
    edge (int node1_, int node2_, int edge_cost_) {
        node1 = node1_;
        node2 = node2_;
        edge_cost = edge_cost_;
    }
    
    edge & operator = (const edge & other) {
        node1 = other.node1;
        node2 = other.node2;
        edge_cost = other.edge_cost;
        return *this;
    }
};

vector<edge> read_file(string file_path) {
    vector<edge> graph;
    ifstream file(file_path);
    string str;
    int index = 0;
    
    while (getline(file, str)) {
        if (index > 0) {
            size_t start = 0;
            int count = 0;
            int node1 = 0;
            int node2 = 0;
            int edge_cost = 0;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == ' ') {
                    string tmp = str.substr(start, i - start);
                    if (count == 0) {
                        node1 = stoi(tmp);
                    } else if (count == 1) {
                        node2 = stoi(tmp);
                    }
                    start = i + 1;
                    count ++;
                }
                
                if (i == str.size() - 1) {
                    string tmp = str.substr(start, i - start + 1);
                    edge_cost = stoi(tmp);
                }
            }
            edge one_edge(node1, node2, edge_cost);
            graph.push_back(one_edge);
        }
        index ++;
    }
    
    return graph;
}

edge find_min_cost(vector<edge> graph) {
    edge result;
    size_t min_indx = 0;
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[i].edge_cost < graph[min_indx].edge_cost) {
            min_indx = i;
        }
    }
    
    result = graph[min_indx];
    return result;
}

bool frontier_check(edge tmp, set<int> v) {
    bool flag = false;
    int node1 = tmp.node1;
    int node2 = tmp.node2;
    //cout << node1 << endl;
    //cout << node2 << endl;
    //cout << (v.find(node1) == v.end()) << endl;
    //cout << (v.find(node2) == v.end()) << endl;
    if (v.find(node1) != v.end() && !(v.find(node2) != v.end())) {
        flag = true;
    }
    if (!(v.find(node1) != v.end()) && v.find(node2) != v.end()) {
        flag = true;
    }
    return flag;
}

edge find_next_min_cost(vector<edge> graph, set<int> &v) {
    edge result;
    size_t min_indx = 0;
    size_t i = 0;
    for (i = 0; i < graph.size(); i++) {
        if (frontier_check(graph[i], v)) {
            min_indx = i;
            break;
        }
    }
    
    for (size_t j = i + 1; j < graph.size(); j++) {
        if (frontier_check(graph[j], v) && graph[j].edge_cost < graph[min_indx].edge_cost) {
            min_indx = j;
        }
    }
    
    result = graph[min_indx];
    v.insert(result.node1);
    v.insert(result.node2);
    return result;
}

vector<edge> mst(vector<edge> graph) {
    edge edge_with_min_cost;
    set<int> v;
    edge_with_min_cost = find_min_cost(graph);
    v.insert(edge_with_min_cost.node1);
    v.insert(edge_with_min_cost.node2);
    vector<edge> result;
    result.push_back(edge_with_min_cost);
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (v.size() == 500) {
            break;
        }
        result.push_back(find_next_min_cost(graph, v));
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    string file_path = "/Users/JamesGuo/git_master/Algorithms/edges.txt";
    vector<edge> graph = read_file(file_path);
    vector<edge> mini_spanning_tree = mst(graph);
    int mini_cost = 0;
    for (size_t i = 0; i < mini_spanning_tree.size(); i++) {
        mini_cost += mini_spanning_tree[i].edge_cost;
    }
    std::cout << "The cost for Minimum Spanning Tree is " << mini_cost << endl;
    return 0;
}
