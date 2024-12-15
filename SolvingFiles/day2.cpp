#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iterator>
#include <fstream>
#include "mainh.h"

using namespace std;

bool is_safe_sequence(const vector<int>& nums) {
    if (nums.size() <= 1) {
        return true;
    }

    vector<int> differences;
    for (size_t i = 1; i < nums.size(); ++i) {
        differences.push_back(nums[i] - nums[i - 1]);
    }

    bool should_increase = differences[0] > 0;

    for (int diff : differences) {
        if ((should_increase && diff <= 0) || (!should_increase && diff >= 0)) {
            return false;
        }

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
    }

    return true;
}

bool is_safe_with_dampener(const string& line, bool use_dampener) {
    vector<int> nums;
    stringstream ss(line);
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }

    if (is_safe_sequence(nums)) {
        return true;
    }

    if (!use_dampener) {
        return false;
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        vector<int> dampened_nums = nums;
        dampened_nums.erase(dampened_nums.begin() + i);
        if (is_safe_sequence(dampened_nums)) {
            return true;
        }
    }

    return false;
}

int count_safe_reports(const string& input, bool use_dampener) {
    stringstream ss(input);
    string line;
    int count = 0;

    while (getline(ss, line)) {
        if (!line.empty() && is_safe_with_dampener(line, use_dampener)) {
            ++count;
        }
    }

    return count;
}


string load_file(const string& filename) {
    ifstream file(filename);

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void day_2() {
    string filename = "input2.txt";
    string input = load_file(filename);

    int part1 = count_safe_reports(input, false);
    int part2 = count_safe_reports(input, true);

    cout << part1 << endl;
    cout << part2 << endl;
}

