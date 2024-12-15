#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "mainh.h"

using namespace std;

void day_3() {
    ifstream file("input3.txt");

    string line;
    long long s1 = 0;
    regex mul_pattern(R"(mul\((\d+),(\d+)\))");

    while (getline(file, line)) {
        smatch match;
        string::const_iterator search_start(line.cbegin());
        while (regex_search(search_start, line.cend(), match, mul_pattern)) {
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            s1 += x * y;
            search_start = match.suffix().first;
        }
    }

    cout << s1 << endl;
    file.close();

    ifstream file2("input3.txt");

    string s((istreambuf_iterator<char>(file2)), istreambuf_iterator<char>());
    file2.close();

    long long s2 = 0;
    bool on = true;
    size_t i = 0;

    regex do_pattern(R"(do\(\s*\))");
    regex dont_pattern(R"(don't\(\s*\))");

    while (i < s.size()) {
        smatch do_match, dont_match, mul_match;

        string substr = s.substr(i);
        size_t do_pos = regex_search(substr, do_match, do_pattern) ? do_match.position(0) + i : string::npos;
        size_t dont_pos = regex_search(substr, dont_match, dont_pattern) ? dont_match.position(0) + i : string::npos;
        size_t mul_pos = regex_search(substr, mul_match, mul_pattern) ? mul_match.position(0) + i : string::npos;

        if (do_pos == string::npos && dont_pos == string::npos && mul_pos == string::npos)
            break;

        if (do_pos != string::npos && (dont_pos == string::npos || do_pos < dont_pos) && (mul_pos == string::npos || do_pos < mul_pos)) {
            on = true;
            i = do_pos + do_match[0].length();
        }
        else if (dont_pos != string::npos && (do_pos == string::npos || dont_pos < do_pos) && (mul_pos == string::npos || dont_pos < mul_pos)) {
            on = false;
            i = dont_pos + dont_match[0].length();
        }
        else if (mul_pos != string::npos && (do_pos == string::npos || mul_pos < do_pos) && (dont_pos == string::npos || mul_pos < dont_pos)) {
            if (on) {
                int x = stoi(mul_match[1].str());
                int y = stoi(mul_match[2].str());
                s2 += x * y;
            }
            i = mul_pos + mul_match[0].length();
        }
    }

    cout << s2 << endl;
}

