#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include "mainh.h"

std::string strip(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }

    return str.substr(first, last - first + 1);
}

int day9_1() {
    std::string file_path = "input9.txt";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file " << file_path << '\n';
        return 1;
    }

    std::string inpt;
    std::string line;
    while (std::getline(file, line)) {
        line = strip(line);
        if (line.empty()) {
            continue;
        }
        inpt = line;
    }

    file.close();

    if (inpt.empty()) {
        std::cerr << "Input file is empty or does not contain valid data." << std::endl;
        return 1;
    }

    std::vector<int64_t> array;
    bool place = true;
    int64_t curid = 0;
    size_t first_none = std::string::npos;

    for (char ch : inpt) {
        int x = ch - '0';
        for (int i = 0; i < x; ++i) {
            if (place) {
                array.push_back(curid);
            }
            else {
                if (first_none == std::string::npos) {
                    first_none = array.size();
                }
                array.push_back(-1);
            }
        }
        if (place) {
            ++curid;
        }
        place = !place;
    }

    while (first_none < array.size()) {
        while (!array.empty() && array.back() == -1) {
            array.pop_back();
        }

        if (first_none >= array.size()) {
            break;
        }

        array[first_none] = array.back();
        array.pop_back();

        while (first_none < array.size() && array[first_none] != -1) {
            ++first_none;
        }
    }

    int64_t ans = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        ans += i * array[i];
    }

    std::cout << ans << std::endl;

    return 0;
}

int day9_2() {
    std::string file_path = "input9.txt";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file " << file_path << '\n';
        return 1;
    }

    std::string inpt;
    std::string line;
    while (std::getline(file, line)) {
        line = strip(line);
        if (line.empty()) {
            continue;
        }
        inpt = line;
    }

    file.close();

    if (inpt.empty()) {
        std::cerr << "Input file is empty or does not contain valid data." << std::endl;
        return 1;
    }

    std::vector<std::pair<int64_t, int64_t>> filled;
    int64_t curid = 0;
    int64_t first_gap = -1;
    bool place = true;

    for (char ch : inpt) {
        int64_t x = ch - '0';
        if (place) {
            filled.emplace_back(curid, x);
        }
        else {
            if (first_gap == -1) {
                first_gap = filled.size();
            }
            filled.emplace_back(-1, x);
        }
        if (place) {
            ++curid;
        }
        place = !place;
    }

    int64_t id_to_move = curid - 1;

    while (id_to_move >= 0) {
        int64_t top_idx = filled.size() - 1;
        while (filled[top_idx].first != id_to_move) {
            --top_idx;
        }

        for (int64_t i = 0; i < top_idx; ++i) {
            if (filled[i].first == -1 && filled[i].second >= filled[top_idx].second) {
                int64_t space_left = filled[i].second - filled[top_idx].second;
                filled.insert(filled.begin() + i, { filled[top_idx].first, filled[top_idx].second });
                filled.insert(filled.begin() + i + 1, { -1, space_left });
                filled.erase(filled.begin() + top_idx + 2);
                break;
            }
        }

        --id_to_move;
        std::vector<std::pair<int64_t, int64_t>> new_filled;
        int64_t cur_space = 0;

        for (const auto& [a, b] : filled) {
            if (a != -1) {
                if (cur_space > 0) {
                    new_filled.emplace_back(-1, cur_space);
                }
                cur_space = 0;
                new_filled.emplace_back(a, b);
            }
            else {
                cur_space += b;
            }
        }

        filled = std::move(new_filled);
    }

    int64_t ans = 0;
    int64_t loc = 0;

    for (const auto& [a, b] : filled) {
        if (a != -1) {
            for (int64_t x = 0; x < b; ++x) {
                ans += loc * a;
                ++loc;
            }
        }
        else {
            loc += b;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}

void day_9() {
    day9_1();
    day9_2();
}
