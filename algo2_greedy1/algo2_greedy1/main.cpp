//
//  main.cpp
//  algo2_greedy1
//
//  Created by Xin Guo on 29/07/15.
//  Copyright (c) 2015 JamesGuo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class job {
public:
    int job_id;
    int weight;
    int length;
    int diff;
    
    job (int job_id_, int weight_, int length_) {
        job_id = job_id_;
        weight = weight_;
        length = length_;
        diff = weight_ - length_;
    }
};

vector<job> read_file(string file_path) {
    vector<job> jobs;
    ifstream file(file_path);
    string str;
    int index = 0;
    int num_jobs;
    
    while (getline(file, str)) {
        if (index == 0) {
            num_jobs = stoi(str);
        } else {
            int weight = 0;
            int length = 0;
            string substr;
            size_t start = 0;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == ' ') {
                    substr = str.substr(start, i - start);
                    weight = stoi(substr);
                    start = i + 1;
                }
                
                if (i == str.size() - 1) {
                    substr = str.substr(start, i - start + 1);
                    length = stoi(substr);
                }
            }
            job tmp(index - 1, weight, length);
            jobs.push_back(tmp);
        }
        index ++;
    }
    
    return jobs;
}

void sort_diff_helper(vector<job> &sorted_jobs, job item) {
    if (sorted_jobs.size() == 0) {
        sorted_jobs.push_back(item);
        return;
    } else {
        for (size_t i = 0; i < sorted_jobs.size(); i++) {
            if (sorted_jobs[i].diff > item.diff) {
                if (i == sorted_jobs.size() - 1) {
                    sorted_jobs.push_back(item);
                    break;
                }
                continue;
            } else if (sorted_jobs[i].diff == item.diff) {
                if (sorted_jobs[i].weight > item.weight) {
                    if (i == sorted_jobs.size() - 1) {
                        sorted_jobs.push_back(item);
                        break;
                    }
                    continue;
                } else {
                    sorted_jobs.insert(sorted_jobs.begin() + i, item);
                    break;
                }
            } else {
                sorted_jobs.insert(sorted_jobs.begin() + i, item);
                break;
            }
// SOME ITEM IS NOT ADDED INTO SORTED_JOBS
        }
        return;
    }
}


vector<job> sort_diff(vector<job> jobs) {
    vector<job> sorted_jobs;
    for (size_t i = 0; i < jobs.size(); i++) {
        sort_diff_helper(sorted_jobs, jobs[i]);
    }
    
    return sorted_jobs;
}

long long int compute_weighted_sum(vector<job> sorted_jobs) {
    long long int sum = 0;
    long long int sum_length = 0;
    for (size_t i = 0; i < sorted_jobs.size(); i++) {
        sum_length = sum_length + sorted_jobs[i].length;
        sum = sum + sorted_jobs[i].weight * sum_length;
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    string file_path = "/Users/JamesGuo/git_master/Algorithms/jobs.txt";
    vector<job> jobs;
    jobs = read_file(file_path);
    vector<job> sorted_jobs = sort_diff(jobs);
    long long int sum = compute_weighted_sum(sorted_jobs);
    std::cout << "Weighted sum according to diff is " << sum << endl;
    return 0;
}
