#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <utility>
#include "mainh.h"


using namespace std;

map<pair<int, int>, char> g;
set<pair<int, int>> seen;
unordered_map<pair<int, int>, set<pair<int, int>>, pair_hash> inner;
unordered_map<pair<int, int>, set<pair<int, int>>, pair_hash> outer;

pair<int, int> dfs(pair<int, int> c) {
    if (seen.count(c)) {
        return { 0, 0 };
    }

    seen.insert(c);
    int x = c.first;
    int y = c.second;
    int area = 1, perimeter = 0;

    vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    for (const auto& [dx, dy] : directions) {
        pair<int, int> nb = { x + dx, y + dy };

        if (g.count(nb) && g[nb] == g[c]) {
            auto [a0, p0] = dfs(nb);
            area += a0;
            perimeter += p0;
        }
        else {
            perimeter += 1;
        }
    }

    return { area, perimeter };
}

void dfs_v(pair<int, int> f, pair<int, int> c) {
    if (seen.count(c)) {
        return;
    }
    seen.insert(c);
    inner[f].insert(c);
    int x = c.first;
    int y = c.second;

    vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    for (const auto& [dx, dy] : directions) {
        pair<int, int> nb = { x + dx, y + dy };

        if (g.count(nb) && g[nb] == g[c]) {
            dfs_v(f, nb);
        }
        else {
            outer[f].insert(nb);
        }
    }
}

int day12_1() {
    ifstream file("input12.txt");
    vector<string> ls;
    string line;

    while (getline(file, line)) {
        ls.push_back(line);
    }
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[i].size(); ++j) {
            g[{i, j}] = ls[i][j];
        }
    }

    long long result = 0;

    for (const auto& [k, v] : g) {
        if (!seen.count(k)) {
            auto [area, perimeter] = dfs(k);
            result += static_cast<long long>(area) * perimeter;
        }
    }

    std::cout << result << endl;

    return 0;
}

int day12_2() {
    ifstream file("input12.txt");
    vector<string> ls;
    string line;

    while (getline(file, line)) {
        ls.push_back(line);
    }

    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[i].size(); ++j) {
            g[{i, j}] = ls[i][j];
        }
    }

    for (const auto& [k, v] : g) {
        if (!seen.count(k)) {
            dfs_v(k, k);
        }
    }

    long long t = 0;

    for (const auto& [k, _] : g) {
        int c = 0;
        for (const auto& [x, y] : inner[k]) {
            vector<pair<pair<int, int>, pair<int, int>>> checks = {
                {{-1, 0}, {0, -1}},
                {{1, 0}, {0, 1}},
                {{-1, 0}, {0, 1}},
                {{1, 0}, {0, -1}}
            };

            for (const auto& [c0, c1] : checks) {
                if (outer[k].count({ x + c0.first, y + c0.second }) &&
                    outer[k].count({ x + c1.first, y + c1.second })) {
                    c++;
                }
                else if (inner[k].count({ x + c0.first, y + c0.second }) &&
                    inner[k].count({ x + c1.first, y + c1.second }) &&
                    outer[k].count({ x + c0.first + c1.first, y + c0.second + c1.second })) {
                    c++;
                }
            }
        }

        t += inner[k].size() + 13;
    }

    std::cout << t << endl;

    return 0;
}

void day_12() {
    day12_1();
    day12_2();
}
