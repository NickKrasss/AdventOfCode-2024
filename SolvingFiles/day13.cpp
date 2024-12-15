#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include "mainh.h"

using namespace std;

int day13_1() {
    ifstream file("input13.txt");
    if (!file.is_open()) {
        cerr << "Error: Cannot open file input3.txt" << endl;
        return 1;
    }

    string line;
    pair<int, int> cura, curb;
    int ans = 0;
    int st = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            st = 0;
            continue;
        }

        istringstream iss(line);
        string toks[4];

        if (st == 0) {
            for (int i = 0; i < 4; ++i) {
                iss >> toks[i];
            }
            int x = stoi(toks[2].substr(2, toks[2].size() - 3));
            int y = stoi(toks[3].substr(2));
            cura = { x, y };
            st = 1;
        }
        else if (st == 1) {
            for (int i = 0; i < 4; ++i) {
                iss >> toks[i];
            }
            int x = stoi(toks[2].substr(2, toks[2].size() - 3));
            int y = stoi(toks[3].substr(2));
            curb = { x, y };
            st = 2;
        }
        else {
            for (int i = 0; i < 3; ++i) {
                iss >> toks[i];
            }
            int x = stoi(toks[1].substr(2, toks[1].size() - 3));
            int y = stoi(toks[2].substr(2));

            int score = numeric_limits<int>::max();

            for (int i = 0; i <= 100; ++i) {
                for (int j = 0; j <= 100; ++j) {
                    if (i * cura.first + j * curb.first == x && i * cura.second + j * curb.second == y) {
                        score = min(score, 3 * i + j);
                    }
                }
            }

            if (score < numeric_limits<int>::max()) {
                ans += score;
            }

            st = 0;
        }
    }

    cout << ans << endl;

    return 0;
}
int day13_2() {
    ifstream file("input13.txt");
    if (!file.is_open()) {
        cerr << "Error: Cannot open file input3.txt" << endl;
        return 1;
    }

    string line;
    pair<int, int> cura, curb;
    long long ans = 0;
    int st = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            st = 0;
            continue;
        }

        istringstream iss(line);
        string toks[4];

        if (st == 0) {
            for (int i = 0; i < 4; ++i) {
                iss >> toks[i];
            }
            int x = stoi(toks[2].substr(2, toks[2].size() - 3));
            int y = stoi(toks[3].substr(2));
            cura = { x, y };
            st = 1;
        }
        else if (st == 1) {
            for (int i = 0; i < 4; ++i) {
                iss >> toks[i];
            }
            int x = stoi(toks[2].substr(2, toks[2].size() - 3));
            int y = stoi(toks[3].substr(2));
            curb = { x, y };
            st = 2;
        }
        else {
            for (int i = 0; i < 3; ++i) {
                iss >> toks[i];
            }
            long long x = stoll(toks[1].substr(2, toks[1].size() - 3)) + 10000000000000LL;
            long long y = stoll(toks[2].substr(2)) + 10000000000000LL;

            long long a = cura.first, b = curb.first, c = cura.second, d = curb.second;
            long long det = a * d - b * c;

            if (det != 0) {
                long long i_numerator = d * x - b * y;
                long long j_numerator = -c * x + a * y;

                if (i_numerator % det == 0 && j_numerator % det == 0) {
                    long long i = i_numerator / det;
                    long long j = j_numerator / det;

                    if (i > 0 && j > 0) {
                        assert(a * i + b * j == x);
                        assert(c * i + d * j == y);
                        ans += 3 * i + j;
                    }
                }
            }

            st = 0;
        }
    }

    cout << ans << endl;

    return 0;
}
void day_13() {
    day13_1();
    day13_2();
}
