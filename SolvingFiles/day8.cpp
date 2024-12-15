#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>
#include "mainh.h"

using namespace std;

typedef pair<int, int> Point;

int day8_1() {
    unordered_set<Point, PointHash> antinodes;
    vector<string> grid;

    ifstream file("input8.txt");
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    file.close();

    int N = grid.size();
    int M = grid[0].size();

    unordered_map<char, vector<Point>> nodes;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] != '.') {
                nodes[grid[i][j]].emplace_back(i, j);
            }
        }
    }

    auto antinode = [&](const Point& pr1, const Point& pr2) {
        int x1 = pr1.first, y1 = pr1.second;
        int x2 = pr2.first, y2 = pr2.second;
        int newx = x2 + (x2 - x1);
        int newy = y2 + (y2 - y1);
        if (newx >= 0 && newx < N && newy >= 0 && newy < M) {
            antinodes.insert({ newx, newy });
        }
        };

    for (const auto& [key, node_list] : nodes) {
        int L = node_list.size();
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < i; ++j) {
                antinode(node_list[i], node_list[j]);
                antinode(node_list[j], node_list[i]);
            }
        }
    }


    cout << antinodes.size() << endl;

    return 0;
}

int day8_2() {
    unordered_set<Point, PointHash> antinodes;
    vector<string> grid;

    ifstream file("input8.txt");
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    file.close();

    int N = grid.size();
    int M = grid[0].size();

    unordered_map<char, vector<Point>> nodes;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] != '.') {
                nodes[grid[i][j]].emplace_back(i, j);
            }
        }
    }

    auto antinode = [&](const Point& pr1, const Point& pr2) {
        int x1 = pr1.first, y1 = pr1.second;
        int x2 = pr2.first, y2 = pr2.second;
        int newx = x2 + (x2 - x1);
        int newy = y2 + (y2 - y1);
        antinodes.insert({ x2, y2 });
        while (0 <= newx && newx < N && 0 <= newy && newy < M) {
            antinodes.insert({ newx, newy });
            newx += (x2 - x1);
            newy += (y2 - y1);
        }
        };

    for (const auto& [key, node_list] : nodes) {
        int L = node_list.size();
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < i; ++j) {
                antinode(node_list[i], node_list[j]);
                antinode(node_list[j], node_list[i]);
            }
        }
    }

    cout << antinodes.size() << endl;

    return 0;
}

void day_8() {
    day8_1();
    day8_2();
}