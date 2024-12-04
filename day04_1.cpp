#include <fstream>
#include <iostream>
#include <vector>
#include <string>

bool is_valid(const int x, const int y, const std::vector<std::string>::size_type rows, const std::vector<std::string>::size_type cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int search_xmas(const std::vector<std::string>& grid) {
    const std::vector<std::string>::size_type rows = grid.size();
    const std::vector<std::string>::size_type cols = grid[0].size();

    const std::string target = "XMAS";
    const std::basic_string<char>::size_type wordLength = target.size();

    int count = 0;

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1},  // Horizontal: right, left
        {1, 0}, {-1, 0},  // Vertical: down, up
        {1, 1}, {-1, -1}, // Diagonal: down-right, up-left
        {1, -1}, {-1, 1}  // Diagonal: down-left, up-right
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (auto [dx, dy] : directions) {
                int k = 0;
                int x = i, y = j;

                while (k < wordLength && is_valid(x, y, rows, cols) && grid[x][y] == target[k]) {
                    x += dx;
                    y += dy;
                    k++;
                }

                if (k == wordLength) {
                    count++;
                }
            }
        }
    }

    return count;
}

int day04_1(const std::string &file_path)
{
    std::ifstream inputFile(file_path);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;

    while (getline(inputFile, line)) {
        grid.push_back(line);
    }

    inputFile.close();

    return search_xmas(grid);
}