//
//  main.cpp
//  scc
//
//  Created by Xin Guo on 09/12/14.
//  Copyright (c) 2014 JamesGuo. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <time.h>

class Tools {
public:
    std::map<int, std::vector<int>> readTxt(std::string path) {
        std::map<int, std::vector<int>> result;
        std::vector<int> vline;
        std::ifstream file(path);
        std::string str;
        
        while(std::getline(file, str)) {
            vline = parseLine(str);
            result[vline[0]].push_back(vline[1]);
            //std::cout << result[vline[0]].back() << std::endl;
        }
        return result;
    }
    
    std::vector<int> parseLine(std::string line) {
        std::vector<int> result;
        std::string integer;
        int tmp;
        size_t index = 0;
        //std::cout << line.size() << std::endl;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                integer = line.substr(index, i - index);
                index = i + 1;
                tmp = atoi(integer.c_str());
                result.push_back(tmp);
            }
        }
        return result;
    }

};

// DONE: Using stack to implement a non-recursive version of DFS
class dir_graph {
public:
    std::map<int, std::vector<int>> graph;
    std::map<int, std::vector<int>> reversed_graph;
    std::map<int, int> process_order_r;
    std::map<int, int> finish_time;
    std::vector<int> leader_list;
    int t;
    int V;
    
    dir_graph(std::map<int, std::vector<int>> adjacencyList, int ve) {
        graph = adjacencyList;
        V = ve;    // Number of vertices we will deal with
        t = 0;     // Global variable to record time
        leader_list.assign(this->V, 0);
    }
    
    void reverse() {
        int key;
        int node;
        std::vector<int> value;
        std::map<int, std::vector<int>>::iterator iterator;
        for (iterator = graph.begin(); iterator != graph.end(); iterator++) {
            key = iterator->first;
            value = iterator->second;
            for (std::vector<int>::size_type i = 0; i < value.size(); i++) {
                node = value.at(i);
                reversed_graph[node].push_back(key);
            }
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    void DFS_reversed() {
        //std::cout << reversed_graph.size() << std::endl;
        std::stack<int> nodes2process;
        std::set<int> nodes_seen;
        int start, node, value;
        
        for (int i = 1; i <= V; i++) {
            start = i;
            nodes2process.push(start);
            
            while (!nodes2process.empty()) {
                node = nodes2process.top();
                if (nodes_seen.find(node) == nodes_seen.end()) {
                    nodes_seen.insert(node);
                    if (reversed_graph.find(node) != reversed_graph.end()) {
                        for (size_t j = 0; j < reversed_graph.at(node).size(); j++) {
                            value = reversed_graph.at(node).at(j);
                            if (nodes_seen.find(value) == nodes_seen.end()) {
                                nodes2process.push(value);
                            }
                        }
                    }
                } else {
                    nodes2process.pop();
                    //std::cout << "Node is " << node << std::endl;
                    //std::cout << "Finishing time is " << t << std::endl;
                    if (finish_time.find(node) == finish_time.end()) {
                        t++;
                        finish_time[node] = t;
                        process_order_r[t] = node;
                    }
                }
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    void SCC() {
        std::vector<bool> visited;
        visited.assign(V, false);
        std::stack<int> nodes2process;
        int leader, node, value;
        
        for (size_t i = process_order_r.size(); i >= 1; i--) {
            leader = process_order_r.at(int(i));
            nodes2process.push(leader);
            
            while (!nodes2process.empty()) {
                node = nodes2process.top();
                nodes2process.pop();
                if (!visited[node - 1]) {
                    visited[node - 1] = true;
                    leader_list[leader - 1] = leader_list[leader - 1] + 1;
                    if (graph.find(node) != graph.end()) {
                        for (size_t j = 0; j < graph.at(node).size(); j++) {
                            value = graph.at(node).at(j);
                            nodes2process.push(value);
                        }
                    }
                }
                
            }
        }
    }
    
    void print5() {
        std::sort(leader_list.begin(), leader_list.end(), std::greater<int>());
        
        for (size_t index = 0; index < 5; index++ ) {
            std::cout << leader_list[index] << std::endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    Tools tool;
    std::map<int, std::vector<int>> directed_graph;
    std::string path = "/Users/JamesGuo/git_master/Algorithms/SCC.txt";
    int ve = 875714;
    directed_graph = tool.readTxt(path);
    dir_graph d_graph(directed_graph, ve);
    d_graph.reverse();
    d_graph.DFS_reversed();
    d_graph.SCC();
    d_graph.print5();
    return 0;
}
