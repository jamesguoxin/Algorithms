//
//  main.cpp
//  minCuts
//
//  Created by Xin Guo on 07/11/14.
//  Copyright (c) 2014 JamesGuo. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

class Tools {
public:
    std::vector<std::vector<int>> readTxt(std::string path) {
        std::vector<std::vector<int>> result;
        std::vector<int> vline;
        std::ifstream file(path);
        std::string str;
        
        while(std::getline(file, str)) {
            vline = parseLine(str);
            result.push_back(vline);
        }
        return result;
    }
    
    std::vector<int> parseLine(std::string line) {
        std::vector<int> result;
        std::string integer;
        int tmp;
        size_t index = 0;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '\t' || i == line.size()) {
                integer = line.substr(index, i - index);
                index = i + 1;
                tmp = atoi(integer.c_str());
                result.push_back(tmp);
            }
        }
        return result;
    }
};

class uGraph {
public:
    std::vector<std::vector<int>> adjacencyList;
    int nbVertices;

    uGraph(std::vector<std::vector<int>> graph, int nbVer) {
        this->adjacencyList = graph;
        this->nbVertices = nbVer;
    }
    // column must be larger than 0
    void Contraction(int row, int column) {
        int label = this->adjacencyList[row][0];
        int delVer = this->adjacencyList[row][column];
        std::vector<size_t> markToDelete;
        if (label == delVer) {
            std::cout << "Error: label is the same as delVer" << std::endl;
        }
        //std::cout << "row is " << row << std::endl;
        //std::cout << "column is " << column << std::endl;
        //std::cout << "label is " << label << std::endl;
        //std::cout << "delVer is " << delVer << std::endl;
        //std::cout << "start constraction"<< std::endl;
        // find the row represent delVer, push back vertices connected to delVer to label
        for (size_t i = 0; i < this->adjacencyList.size(); i++) {
            if (this->adjacencyList[i][0] == delVer) {
                //std::cout << "the row has delVer " << delVer << " as header is " << i << std::endl;
                //std::cout << "the row has label " << label << " as header is " << row << std::endl;
                for (size_t j = 1; j < this->adjacencyList[i].size(); j++) {
                    if (this->adjacencyList[i][j] != label) {
                        this->adjacencyList[row].push_back(this->adjacencyList[i][j]);
                        //std::cout << "The vertex add to label is " << this->adjacencyList[i][j] <<std::endl;
                    }
                }
                //std::cout << "Finish Adding" << std::endl;
                // for vertices connected to label, delete delVer
                for (size_t j = 1; j < this->adjacencyList[row].size(); j++) {
                    if (this->adjacencyList[row][j] == delVer) {
                        //this->adjacencyList[row].erase(this->adjacencyList[row].begin() + j);
                        markToDelete.push_back(j);
                    }
                }
                
                for (size_t j = 0; j < markToDelete.size(); j++) {
                    this->adjacencyList[row].erase(this->adjacencyList[row].begin() + markToDelete[j] - j);
                }
                
                if (!checkDelVer(this->adjacencyList[row], delVer)) {
                    std::cout << "There will be self-loops" << std::endl;
                }
                if (!check(this->adjacencyList[row])) {
                    std::cout << "There are self-loops" << std::endl;
                }
                this->adjacencyList.erase(this->adjacencyList.begin() + i);
                break;
            }
        }
        //std::cout << "delete Vertex delVer"<< std::endl;
        // since delVer and lable are combined together, change all delVer to label
        for (size_t i = 0; i < this->adjacencyList.size(); i++) {
            for (size_t j = 1; j < this->adjacencyList[i].size(); j++) {
                if (this->adjacencyList[i][j] == delVer) {
                    this->adjacencyList[i][j] = label;
                }
            }
        }
        
        for (size_t i = 0; i < this->adjacencyList.size(); i++) {
            if (!check(this->adjacencyList[i])) {
                std::cout << "Error happens at row " << i << std::endl;
            }
        }
        //std::cout << "Change all delVer to label" << std::endl;
        
        //std::cout << "delete self-loop" << std::endl;
        this->nbVertices = this->nbVertices - 1;
    }
    
    void setValues(std::vector<std::vector<int>> graph, int nbVer) {
        this->adjacencyList = graph;
        this->nbVertices = nbVer;
    }
    
    bool check(std::vector<int> rowx) {
        int checker = rowx[0];
        for (size_t i = 1; i < rowx.size(); i++) {
            if (rowx[i] == checker) {
                return false;
            }
        }
        return true;
    }
    
    bool checkDelVer(std::vector<int> rowx, int checker) {
        for (size_t i = 0; i < rowx.size(); i++) {
            if (rowx[i] == checker) {
                return false;
            }
        }
        return true;
    }
    
    size_t minCut() {
        if (this->nbVertices == 2) {
            return (this->adjacencyList[0].size() - 1);
        } else {
            std::perror("The number of Vertices is not TWO!!");
        }
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    std::string path = "/Users/JamesGuo/git_master/Algorithms/kargerMinCut.txt";
    std::vector<std::vector<int>> graph;
    int row, column;
    size_t minimum = 19900;
    Tools tool;
    graph = tool.readTxt(path);
    for (size_t i = 0; i < 80000; i++) {
        srand((unsigned int)time(NULL));
        uGraph undirectedGraph(graph, 200);
        while (undirectedGraph.nbVertices > 2) {
            row = rand() % undirectedGraph.adjacencyList.size();
            column = rand() % undirectedGraph.adjacencyList[row].size();
            if (column == 0) {
                column = 1;
            }
            undirectedGraph.Contraction(row, column);
            //std::cout << undirectedGraph.nbVertices << std::endl;
        }
        if (minimum > undirectedGraph.minCut()) {
            minimum = undirectedGraph.minCut();
        }
        //std::cout << i << std::endl;
    }
    std::cout << minimum << std::endl;
    return 0;
}
