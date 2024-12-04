#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int search_mas(const std::vector<std::string>& grid) {
    const std::vector<std::string>::size_type rows = grid.size();
    const std::vector<std::string>::size_type cols = grid[0].size();

    int count = 0;

    for (int i = 1; i < rows - 1; ++i)
        {
        for (int j = 1; j < cols - 1; ++j)
            {
            const bool forwardMAS = (grid[i-1][j-1] == 'M' && grid[i][j] == 'A' && grid[i+1][j+1] == 'S') &&
                              (grid[i-1][j+1] == 'M' && grid[i][j] == 'A' && grid[i+1][j-1] == 'S');

            const bool backwardMAS = (grid[i-1][j-1] == 'S' && grid[i][j] == 'A' && grid[i+1][j+1] == 'M') &&
                               (grid[i-1][j+1] == 'S' && grid[i][j] == 'A' && grid[i+1][j-1] == 'M');

            const bool mixedMAS = (grid[i-1][j-1] == 'M' && grid[i][j] == 'A' && grid[i+1][j+1] == 'S') &&
                              (grid[i-1][j+1] == 'S' && grid[i][j] == 'A' && grid[i+1][j-1] == 'M');

            const bool mixedSAM = (grid[i-1][j-1] == 'S' && grid[i][j] == 'A' && grid[i+1][j+1] == 'M') &&
                               (grid[i-1][j+1] == 'M' && grid[i][j] == 'A' && grid[i+1][j-1] == 'S');

            if (forwardMAS || backwardMAS || mixedMAS || mixedSAM) {
                count++;
            }
        }
    }

    return count;
}

int day04_2(const std::string &file_path)
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

    return search_mas(grid);
}
