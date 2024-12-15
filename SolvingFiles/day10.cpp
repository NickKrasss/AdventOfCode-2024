#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include "mainh.h"

int day10_1() {
    std::string file_path = "input10.txt";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file " << file_path << '\n';
        return 1;
    }

    std::vector<std::string> ls;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            ls.push_back(line);
        }
    }

    file.close();

    if (ls.empty()) {
        std::cerr << "Input file is empty or does not contain valid data." << std::endl;
        return 1;
    }

    std::map<std::pair<int, int>, char> grid;
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[i].size(); ++j) {
            grid[{i, j}] = ls[i][j];
        }
    }

    std::deque<std::pair<std::pair<int, int>, std::pair<int, int>>> q;
    std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> seen;

    for (const auto& [pos, val] : grid) {
        if (val == '0') {
            q.push_back({ pos, pos });
        }
    }

    while (!q.empty()) {
        auto [start, current] = q.front();
        q.pop_front();

        if (grid[current] == '9') {
            seen.insert({ start, current });
            continue;
        }

        auto [x, y] = current;
        for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{ {1, 0}, {0, 1}, {0, -1}, {-1, 0} }) {
            int nx = x + dx;
            int ny = y + dy;

            auto next = std::make_pair(nx, ny);
            if (grid.find(next) != grid.end() && grid[next] == (char)(grid[current] + 1)) {
                q.push_back({ start, next });
            }
        }
    }

    std::cout << seen.size() << std::endl;
    return 0;
}
int day10_2() {
    std::string file_path = "input10.txt";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file " << file_path << '\n';
        return 1;
    }

    std::vector<std::string> ls;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            ls.push_back(line);
        }
    }

    file.close();

    if (ls.empty()) {
        std::cerr << "Input file is empty or does not contain valid data." << std::endl;
        return 1;
    }

    std::map<std::pair<int, int>, char> grid;
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[i].size(); ++j) {
            grid[{i, j}] = ls[i][j];
        }
    }

    std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> q;
    int t = 0;

    for (const auto& [pos, val] : grid) {
        if (val == '0') {
            q.push({ pos, pos });
        }
    }

    while (!q.empty()) {
        auto [start, current] = q.front();
        q.pop();

        if (grid[current] == '9') {
            ++t;
            continue;
        }

        auto [x, y] = current;
        for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{ {1, 0}, {0, 1}, {0, -1}, {-1, 0} }) {
            int nx = x + dx;
            int ny = y + dy;

            auto next = std::make_pair(nx, ny);
            if (grid.find(next) != grid.end() && grid[next] == (char)(grid[current] + 1)) {
                q.push({ start, next });
            }
        }
    }

    std::cout << t << std::endl;
    return 0;
}

void day_10() {
    day10_1();
    day10_2();
}