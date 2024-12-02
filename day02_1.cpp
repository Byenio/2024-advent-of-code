#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool is_safe(const std::vector<int> &levels)
{
    const bool ascending = levels[0] < levels[1];

    for (int i = 0; i < levels.size() - 1; i++)
    {
        constexpr int min_diff = 1;
        constexpr int max_diff = 3;
        const int abs_diff = abs(levels[i] - levels[i + 1]);

        if (ascending)
        {
            const bool is_ascending = levels[i] < levels[i + 1];
            const bool is_diff_gradual = (abs_diff <= max_diff) && (abs_diff >= min_diff);

            if (!is_ascending || !is_diff_gradual) return false;
        }

        if (!ascending)
        {
            const bool is_descending = levels[i] > levels[i + 1];
            const bool is_diff_gradual = (abs_diff <= max_diff) && (abs_diff >= min_diff);

            if (!is_descending || !is_diff_gradual) return false;
        }
    }

    return true;
}

int day02_1(const std::string &file_path)
{
    std::fstream file(file_path, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Can't open file" << std::endl;
        return 1;
    }

    std::string line;
    int counter = 0;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> levels;
        int level;

        while (iss >> level)
        {
            levels.push_back(level);
        }

        is_safe(levels) ? counter++ : 0;
    }

    file.close();

    return counter;
}
