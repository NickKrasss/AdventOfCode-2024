#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>
#include <climits>
#include "mainh.h"

using namespace std;

int day16_1() {
    ifstream file("input16.txt");
    string line;
    vector<string> data;

    while (getline(file, line)) {
        data.push_back(line);
    }

    unordered_map<pair<int, int>, char, pair_hash_16> g; 
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            g[{i, j}] = data[i][j];
        }
    }

    pair<int, int> start, target;


    for (const auto& p : g) {
        if (p.second == 'S') start = p.first;
        if (p.second == 'E') target = p.first;
    }


    priority_queue<tuple<int, pair<int, int>, pair<int, int>>, vector<tuple<int, pair<int, int>, pair<int, int>>>, greater<>> tv;
    tv.push({ 0, start, {0, 1} });

    set<pair<pair<int, int>, pair<int, int>>> SEEN;


    while (!tv.empty()) {
        int s;
        pair<int, int> p;
        pair<int, int> d;
        tie(s, p, d) = tv.top();
        tv.pop();

        if (g[p] == '#') {
            continue;
        }

        if (SEEN.count({ p, d })) {
            continue;
        }

        SEEN.insert({ p, d });

        if (p == target) {
            cout << s << endl;
            break;
        }

        int x = p.first, y = p.second;
        vector<pair<int, int>> directions = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

        for (const auto& dir : directions) {
            int dx = dir.first, dy = dir.second;
            int sa = (dx == d.first && dy == d.second) ? 1 : 1001;
            tv.push({ s + sa, {x + dx, y + dy}, {dx, dy} });
        }
    }

    return 0;
}

int day16_2() {
    ifstream file("input16.txt");
    string line;
    vector<string> data;

    while (getline(file, line)) {
        data.push_back(line);
    }

    unordered_map<Position16, char, PositionHash16> g;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            g[Position16(i, j)] = data[i][j];
        }
    }

    Position16 start, target;

    for (const auto& p : g) {
        if (p.second == 'S') start = p.first;
        if (p.second == 'E') target = p.first;
    }

    priority_queue<tuple<int, vector<Position16>, Position16>,
        vector<tuple<int, vector<Position16>, Position16>>,
        greater<>> tv;
    tv.push({ 0, {start}, Position16(0, 1) });

    unordered_map<std::pair<Position16, Position16>, int, PositionPairHash16> SEEN;
    int best = INT_MAX;
    set<Position16> ans;

    while (!tv.empty()) {
        int s;
        vector<Position16> path;
        Position16 d;
        tie(s, path, d) = tv.top();
        tv.pop();

        if (s > best) {
            continue;
        }

        Position16 p = path.back();

        if (g[p] == '#') {
            continue;
        }

        if (SEEN.count({ p, d }) && SEEN[{p, d}] < s) {
            continue;
        }

        SEEN[{p, d}] = s;

        if (p == target) {
            best = min(best, s);
            if (best == s) {
                for (const auto& point : path) {
                    ans.insert(point);
                }
            }
        }

        int x = p.x, y = p.y;
        vector<Position16> directions = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

        for (const auto& dir : directions) {
            int dx = dir.x, dy = dir.y;
            int sa = (dx == d.x && dy == d.y) ? 1 : 1001;
            vector<Position16> np = path;
            np.push_back(Position16(x + dx, y + dy));
            tv.push({ s + sa, np, Position16(dx, dy) });
        }
    }

    cout << ans.size() << endl;

    return 0;
}

void day_16() {
    day16_1();
    day16_2();
}