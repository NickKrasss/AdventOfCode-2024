#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "mainh.h"

using namespace std;

typedef pair<int, int> Position;
typedef pair<int, int> Velocity;
typedef pair<Position, Velocity> Robot;

const int GRID_WIDTH = 101;
const int GRID_HEIGHT = 103;

vector<Robot> parseInput(const vector<string>& data) {
    vector<Robot> robots;
    for (const auto& line : data) {
        auto spacePos = line.find(' ');
        if (spacePos == string::npos) {
            throw runtime_error("Error parsing input line: " + line);
        }

        string p = line.substr(2, spacePos - 2);
        string v = line.substr(spacePos + 3);

        int px, py, vx, vy;
        try {
            px = stoi(p.substr(0, p.find(',')));
            py = stoi(p.substr(p.find(',') + 1));
            vx = stoi(v.substr(0, v.find(',')));
            vy = stoi(v.substr(v.find(',') + 1));
        }
        catch (const invalid_argument&) {
            throw runtime_error("Error parsing input line: " + line);
        }
        catch (const out_of_range&) {
            throw runtime_error("Value out of range in line: " + line);
        }

        robots.emplace_back(make_pair(px, py), make_pair(vx, vy));
    }
    return robots;
}


Position moveRobot(const Position& position, const Velocity& velocity, int width, int height) {
    int x = (position.first + velocity.first + width) % width;
    int y = (position.second + velocity.second + height) % height;
    return make_pair(x, y);
}

vector<Robot> simulateRobots(const vector<Robot>& robots, int width, int height, int seconds) {
    vector<Robot> result = robots;
    for (int t = 0; t < seconds; ++t) {
        for (auto& robot : result) {
            robot.first = moveRobot(robot.first, robot.second, width, height);
        }
    }
    return result;
}

vector<int> countRobotsInQuadrants(const vector<Robot>& robots, int width, int height) {
    int mid_x = width / 2;
    int mid_y = height / 2;
    vector<int> quadrants(4, 0);

    for (const auto& robot : robots) {
        int x = robot.first.first;
        int y = robot.first.second;

        if (x == mid_x || y == mid_y) continue;

        if (x < mid_x && y < mid_y) {
            ++quadrants[0];
        }
        else if (x >= mid_x && y < mid_y) {
            ++quadrants[1];
        }
        else if (x < mid_x && y >= mid_y) {
            ++quadrants[2];
        }
        else if (x >= mid_x && y >= mid_y) {
            ++quadrants[3];
        }
    }

    return quadrants;
}

bool checkChristmasTreePattern(const vector<Robot>& robots, int width, int height) {
    const vector<string> treePattern = {
        "....#....",
        "...###...",
        "..#####..",
        ".#######.",
        "#########",
        "....#....",
        "....#...."
    };

    int patternHeight = treePattern.size();
    int patternWidth = treePattern[0].size();

    vector<vector<char>> grid(height, vector<char>(width, '.'));
    for (const auto& robot : robots) {
        int x = robot.first.first;
        int y = robot.first.second;
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = '#';
        }
    }

    for (int y = 0; y <= height - patternHeight; ++y) {
        for (int x = 0; x <= width - patternWidth; ++x) {
            bool match = true;
            for (int py = 0; py < patternHeight && match; ++py) {
                for (int px = 0; px < patternWidth; ++px) {
                    if (treePattern[py][px] == '#' && grid[y + py][x + px] != '#') {
                        match = false;
                        break;
                    }
                }
            }
            if (match) return true;
        }
    }
    return false;
}

int findEasterEgg(const vector<string>& data) {
    auto robots = parseInput(data);
    int seconds = 0;

    while (seconds < 100000) { // Prevent infinite loop
        robots = simulateRobots(robots, GRID_WIDTH, GRID_HEIGHT, 1);
        ++seconds;
        if (checkChristmasTreePattern(robots, GRID_WIDTH, GRID_HEIGHT)) {
            return seconds;
        }
    }
    throw runtime_error("Easter egg not found within reasonable time.");
}

int solve(const vector<string>& data) {
    auto robots = parseInput(data);
    robots = simulateRobots(robots, GRID_WIDTH, GRID_HEIGHT, 100);

    auto quadrants = countRobotsInQuadrants(robots, GRID_WIDTH, GRID_HEIGHT);
    int safetyFactor = 1;
    for (int count : quadrants) {
        safetyFactor *= count;
    }
    return safetyFactor;
}

int day_14() {
    ifstream inputFile("input14.txt");
    vector<string> data;
    string line;

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        data.push_back(line);
    }

    inputFile.close();

    try {
        cout << solve(data) << endl;
        cout << findEasterEgg(data) << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
