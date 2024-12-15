#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "mainh.h"

using namespace std;

bool checkWord(const vector<string>& grid, int x, int y, int dx, int dy, const string& word, int rows, int cols) {
    for (size_t i = 0; i < word.size(); ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != word[i]) {
            return false;
        }
    }
    return true;
}
int countXMAS(const vector<string>& grid, int rows, int cols) {
    string targetWord = "XMAS";
    vector<pair<int, int>> directions = {
        {0, 1},   
        {1, 0},   
        {1, 1},   
        {1, -1},  
        {0, -1},  
        {-1, 0},  
        {-1, -1}, 
        {-1, 1}   
    };
    int count = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (const auto& [dx, dy] : directions) {
                if (checkWord(grid, r, c, dx, dy, targetWord, rows, cols)) {
                    count++;
                }
            }
        }
    }
    return count;
}

int countAllXMASPatterns(const vector<string>& grid, int rows, int cols) {
    int count = 0;
    for (int r = 1; r < rows - 1; ++r) {
        for (int c = 1; c < cols - 1; ++c) {
            char center = grid[r][c];
            char topLeft = grid[r - 1][c - 1];
            char topRight = grid[r - 1][c + 1];
            char bottomLeft = grid[r + 1][c - 1];
            char bottomRight = grid[r + 1][c + 1];
            if (center == 'A') {
                if (topLeft == 'M' && topRight == 'S' && bottomLeft == 'M' && bottomRight == 'S') count++;

                if (topLeft == 'S' && topRight == 'M' && bottomLeft == 'S' && bottomRight == 'M') count++;

                if (topLeft == 'M' && topRight == 'M' && bottomLeft == 'S' && bottomRight == 'S') count++;

                if (topLeft == 'S' && topRight == 'S' && bottomLeft == 'M' && bottomRight == 'M') count++;
            }
        }
    }
    return count;
}
void day_4() {
    string filePath = "input4.txt";
    ifstream file(filePath);
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
    int rows = grid.size();
    int cols = grid[0].size();
    int xmasCount = countXMAS(grid, rows, cols);
    cout << xmasCount << endl;
    int xmasPatterns = countAllXMASPatterns(grid, rows, cols);
    cout << xmasPatterns << endl;
}
