#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include "mainh.h"

using namespace std;

pair<int64_t, int64_t> solve_both(const string& input) {
    vector<int64_t> left_numbers;
    vector<int64_t> right_numbers;

    stringstream ss(input);
    string line;
    while (getline(ss, line)) {
        stringstream line_stream(line);
        int64_t left, right;
        if (line_stream >> left >> right) {
            left_numbers.push_back(left);
            right_numbers.push_back(right);
        }
    }

    vector<int64_t> left_sorted = left_numbers;
    vector<int64_t> right_sorted = right_numbers;
    sort(left_sorted.begin(), left_sorted.end());
    sort(right_sorted.begin(), right_sorted.end());

    int64_t total_distance = 0;
    for (size_t i = 0; i < left_sorted.size(); ++i) {
        total_distance += abs(left_sorted[i] - right_sorted[i]);
    }

    unordered_map<int64_t, int64_t> right_counts;
    for (const auto& num : right_numbers) {
        ++right_counts[num];
    }

    int64_t similarity_score = 0;
    for (const auto& num : left_numbers) {
        similarity_score += num * right_counts[num];
    }

    return { total_distance, similarity_score };
}

int64_t solve(const string& input) {
    auto result = solve_both(input);
    return result.second;
}

void day_1() {
    ifstream file("input.txt");

    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();
    file.close();

    auto result = solve_both(input);
    int64_t distance = result.first;
    int64_t similarity = result.second;

    cout << distance << endl;
    cout << similarity << endl;
}
