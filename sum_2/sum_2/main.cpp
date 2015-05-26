//
//  main.cpp
//  sum_2
//
//  Created by Xin Guo on 11/05/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

map<long long int, int> read_file(string path) {
    map<long long int, int> hash_table;
    ifstream file(path);
    string str;
    
    while (getline(file, str)) {
        //str.pop_back();
        long long int value = atoll(str.c_str());
        if (hash_table.find(value) == hash_table.end()) {
            hash_table[value] = 1;
        }
        
    }
    
    return hash_table;
}

int v_2_sum(map<long long int, int> hash_table, vector<long long int> targets) {
    map<long long int, int>::iterator it;
    vector<long long int>::iterator it_v;
    map<long long int, int> targets_found;
    long long int x, y;
    int number = 0;
    int count = 0;
    
    //cout << "There are " << hash_table.size() << " elements need processing" << endl;
    
    for (it = hash_table.begin(); it != hash_table.end(); it++) {
        x = it->first;
        count = count + 1;
        //cout << count <<" elements processed in array" << endl;
        for (it_v = targets.begin(); it_v != targets.end(); it_v++) {
            y = *it_v - x;
            if (x != y) {
                if (hash_table.find(y) != hash_table.end()) {
                    if (targets_found.find(*it_v) == targets_found.end()) {
                        targets_found[*it_v] = 1;
                    }
                }
            }
            
        }
    }
    
    for (it = targets_found.begin(); it != targets_found.end(); it++) {
        number = number + it->second;
    }
    
    return number;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    map<long long int, int> hash_table;
    int number;
    vector<long long int> targets;
    for (long long int i = -10000; i <= 10000; i++) {
        targets.push_back(i);
    }
    string file_path = "/Users/JamesGuo/git_master/Algorithms/algo1-programming_prob-2sum.txt";
    //string file_path = "/Users/JamesGuo/git_master/Algorithms/test_week6_hash.txt";
    hash_table = read_file(file_path);
    number = v_2_sum(hash_table, targets);
    cout << "The number of target value is " << number << endl;
    return 0;
}
