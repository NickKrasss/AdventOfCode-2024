#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cassert>
#include <map>
#include <unordered_map>
#include "mainh.h"

using namespace std;
int ans = 0;
bool st = false;
string moves = "";
vector<vector<char>> origgrid;

int day15_1() {
    ifstream file("input15.txt");
    if (!file.is_open()) {
        cerr << "Error: Cannot open file input15.txt" << endl;
        return 1;
    }

    long long ans = 0;
    bool st = false;
    string moves;
    vector<vector<char>> grid;
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            st = true;
            continue;
        }

        if (st) {
            moves += line;
        }
        else {
            grid.emplace_back(line.begin(), line.end());
        }
    }

    int N = grid.size();
    int M = grid[0].size();
    pair<int, int> cur_loc;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '@') {
                cur_loc = { i, j };
                break;
            }
        }
    }

    unordered_map<char, pair<int, int>> symtodir = {
        {'>', {0, 1}},
        {'<', {0, -1}},
        {'^', {-1, 0}},
        {'v', {1, 0}}
    };

    for (char move : moves) {
        auto dir = symtodir[move];
        pair<int, int> newloc = { cur_loc.first + dir.first, cur_loc.second + dir.second };
        pair<int, int> finalloc = newloc;

        while (grid[finalloc.first][finalloc.second] != '.' && grid[finalloc.first][finalloc.second] != '#') {
            finalloc.first += dir.first;
            finalloc.second += dir.second;
        }

        if (grid[finalloc.first][finalloc.second] != '#') {
            assert(grid[newloc.first][newloc.second] != '#');
            grid[finalloc.first][finalloc.second] = grid[newloc.first][newloc.second];
            grid[newloc.first][newloc.second] = '@';
            grid[cur_loc.first][cur_loc.second] = '.';
            cur_loc = newloc;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'O') {
                ans += 100 * i + j;
            }
        }
    }

    cout << ans << endl;
    return 0;
}

int day15_2() {
    ifstream file("input15.txt");
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            st = true;
            continue;
        }
        if (st) {
            moves += line;
        }
        else {
            vector<char> row(line.begin(), line.end());
            origgrid.push_back(row);
        }
    }

    int N = origgrid.size();
    int M = origgrid[0].size();
    pair<int, int> cur_loc;

    vector<vector<char>> grid(N * 2, vector<char>(M * 2, '.'));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (origgrid[i][j] == '#') {
                grid[i][2 * j] = '#';
                grid[i][2 * j + 1] = '#';
            }
            else if (origgrid[i][j] == 'O') {
                grid[i][2 * j] = '[';
                grid[i][2 * j + 1] = ']';
            }
            else if (origgrid[i][j] == '.') {
                grid[i][2 * j] = '.';
                grid[i][2 * j + 1] = '.';
            }
            else if (origgrid[i][j] == '@') {
                cur_loc = { i, 2 * j };
                grid[i][2 * j] = '@';
                grid[i][2 * j + 1] = '.';
            }
        }
    }

    N = grid.size();
    M = grid[0].size();


    map<char, pair<int, int>> symtodir = {
        {'>', {0, 1}},
        {'<', {0, -1}},
        {'^', {-1, 0}},
        {'v', {1, 0}}
    };

    auto affecting = [&](int x, int y) {
        set<pair<int, int>> result;
        if (grid[x][y] == '.') {
            return result;
        }
        else if (grid[x][y] == '[') {
            result.insert({ x, y });
            result.insert({ x, y + 1 });
        }
        else if (grid[x][y] == ']') {
            result.insert({ x, y });
            result.insert({ x, y - 1 });
        }
        return result;
        };

    for (char move : moves) {
        auto dir = symtodir[move];
        pair<int, int> newloc = { cur_loc.first + dir.first, cur_loc.second + dir.second };

        if (dir.first == 0 || grid[newloc.first][newloc.second] == '.') {
            pair<int, int> finalloc = newloc;
            while (grid[finalloc.first][finalloc.second] != '.' && grid[finalloc.first][finalloc.second] != '#') {
                finalloc.first += dir.first;
                finalloc.second += dir.second;
            }

            if (grid[finalloc.first][finalloc.second] != '#') {
                assert(grid[newloc.first][newloc.second] != '#');
                while (make_pair(finalloc.first - dir.first, finalloc.second - dir.second) != cur_loc) {
                    grid[finalloc.first][finalloc.second] = grid[finalloc.first - dir.first][finalloc.second - dir.second];
                    finalloc.first -= dir.first;
                    finalloc.second -= dir.second;
                }
                grid[newloc.first][newloc.second] = '@';
                grid[cur_loc.first][cur_loc.second] = '.';
                cur_loc = newloc;
            }
        }
        else if (grid[newloc.first][newloc.second] == '#') {
            continue;
        }
        else {
            vector<set<pair<int, int>>> affectings;
            affectings.push_back(affecting(newloc.first, newloc.second));

            bool bad = false;
            while (!affectings.back().empty()) {
                set<pair<int, int>> new_affect;
                for (auto [x, y] : affectings.back()) {
                    if (grid[x + dir.first][y] == '#') {
                        bad = true;
                        break;
                    }
                    for (auto [xd, yd] : affecting(x + dir.first, y)) {
                        new_affect.insert({ xd, yd });
                    }
                }
                if (bad) break;
                affectings.push_back(new_affect);
            }

            if (!bad) {
                for (int i = affectings.size() - 1; i >= 0; --i) {
                    for (auto [x, y] : affectings[i]) {
                        grid[x + dir.first][y] = grid[x][y];
                        grid[x][y] = '.';
                    }
                }
                grid[newloc.first][newloc.second] = '@';
                grid[cur_loc.first][cur_loc.second] = '.';
                cur_loc = newloc;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '[') {
                ans += 100 * i + j;
            }
        }
    }

    cout << ans << endl;

    return 0;
}

void day_15() {
    day15_1();
    day15_2();
}