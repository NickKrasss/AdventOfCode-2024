#pragma once
#define MAINH_H
#ifdef MAINH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>
#include <cstdint>
#include <iterator>
#include <queue>
#include <algorithm>
#include <array>
#include <map>
#include <set>
#include <tuple>
#include <cctype>
#include <limits>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <climits>


//day 1
std::pair<int64_t, int64_t> solve_both(const std::string& input);
int64_t solve(const std::string& input);
void day_1();

//day 2
bool is_safe_sequence(const std::vector<int>& nums);
bool is_safe_with_dampener(const std::string& line, bool use_dampener);
int count_safe_reports(const std::string& input, bool use_dampener);
std::string load_file(const std::string& filename);
void day_2();

//day 3
void day_3();

//day 4
bool checkWord(const std::vector<std::string>& grid, int x, int y, int dx, int dy, const std::string& word, int rows, int cols);
int countXMAS(const std::vector<std::string>& grid, int rows, int cols);
int countAllXMASPatterns(const std::vector<std::string>& grid, int rows, int cols);
void day_4();

//day 5
std::vector<std::string> split(const std::string& str, const std::string& delimiter);
std::string trim(const std::string& s);
bool is_update_ordered(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules);
std::vector<int> topological_sort_update(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules);
int get_middle_page(const std::vector<int>& update);
int day_5();

//day 6
int day6_1();
int day6_2();
void day_6();

//day 7
bool readFile(const std::string& fileName, std::vector<std::string>& lines);
uint64_t concat(uint64_t a, const uint64_t b);
template <bool enableConcatenation = false>
bool check(const std::vector<uint64_t>& ops, uint64_t res, uint64_t interim, size_t i = 1);
int day_7();

//day 8
typedef std::pair<int, int> Point;
struct PointHash {
    size_t operator()(const Point& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};
int day8_1();
int day8_2();
void day_8();

//day 9
std::string strip(const std::string& str);
int day9_1();
int day9_2();
void day_9();

//day 10
int day10_1();
int day10_2();
void day_10();

//day 11
int day_11();

//day 12
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ (h2 << 1);
    }
};
std::pair<int, int> dfs(std::pair<int, int> c);
void dfs_v(std::pair<int, int> f, std::pair<int, int> c);
int day12_1();
int day12_2();
void day_12();

//day 13
int day13_1();
int day13_2();
void day_13();

//day 14
typedef std::pair<int, int> Position;
typedef std::pair<int, int> Velocity;
typedef std::pair<Position, Velocity> Robot;
std::vector<Robot> parseInput(const std::vector<std::string>& data);
Position moveRobot(const Position& position, const Velocity& velocity, int width, int height);
std::vector<Robot> simulateRobots(const std::vector<Robot>& robots, int width, int height, int seconds);
std::vector<int> countRobotsInQuadrants(const std::vector<Robot>& robots, int width, int height);
bool checkChristmasTreePattern(const std::vector<Robot>& robots, int width, int height);
int findEasterEgg(const std::vector<std::string>& data);
int solve(const std::vector<std::string>& data);
int day_14();

//day 15
int day15_1();
int day15_2();
void day_15();

//day 16
struct pair_hash_16 {
    template <class T1, class T2>
    std::size_t operator ()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ (h2 << 1);
    }
};
// Структура Position
struct Position16 {
    int x, y;
    Position16() : x(0), y(0) {}
    Position16(int x, int y) : x(x), y(y) {}

    bool operator==(const Position16& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Position16& other) const {
        // Сравнение сначала по x, потом по y
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

// Хеш-функция для Position16
struct PositionHash16 {
    size_t operator()(const Position16& p) const {
        size_t h1 = std::hash<int>{}(p.x);
        size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1); // Сочетание двух хешей
    }
};

struct PositionPairHash16 {
    size_t operator()(const std::pair<Position16, Position16>& p) const {
        size_t h1 = PositionHash16{}(p.first);  // Хеш для первого элемента пары
        size_t h2 = PositionHash16{}(p.second); // Хеш для второго элемента пары
        return h1 ^ (h2 << 1); // Сочетание хешей
    }
};
struct Compare {
    bool operator()(const std::tuple<int, std::vector<Position16>, Position16>& a,
        const std::tuple<int, std::vector<Position16>, Position16>& b) {
        return get<0>(a) > get<0>(b); // Сравниваем по стоимости пути
    }
};
int day16_1();
int day16_2();
void day_16();


#endif // MAINH_H
