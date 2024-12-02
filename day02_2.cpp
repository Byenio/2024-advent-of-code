#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool is_ascending(const std::vector<int> &levels)
{
    int ascending_count = 0;
    int descending_count = 0;

    for (int i = 0; i < levels.size() - 1; i++)
    {
        if (levels[i] < levels[i + 1])
        {
            ascending_count++;
        } else if (levels[i] > levels[i + 1])
        {
            descending_count++;
        }
    }

    return ascending_count > descending_count;
}

bool is_safe(std::vector<int> &levels, const bool dampened = false)
{
    const bool globally_ascending = is_ascending(levels);

    for (int i = 0; i < levels.size() - 1; i++)
    {
        constexpr int min_diff = 1;
        constexpr int max_diff = 3;
        const int abs_diff = abs(levels[i] - levels[i + 1]);
        const bool is_diff_gradual = (abs_diff >= min_diff) && (abs_diff <= max_diff);

        if (globally_ascending)
        {
            const bool locally_ascending = levels[i] < levels[i + 1];

            if (!locally_ascending || !is_diff_gradual)
            {
                if (!dampened)
                {
                    std::vector<int> temp_levels_1 = levels;
                    std::vector<int> temp_levels_2 = levels;

                    temp_levels_1.erase(temp_levels_1.begin() + i + 1);
                    temp_levels_2.erase(temp_levels_2.begin() + i);

                    return is_safe(temp_levels_1, true) || is_safe(temp_levels_2, true);
                }

                return false;
            }
        }

        if (!globally_ascending)
        {
            const bool locally_descending = levels[i] > levels[i + 1];

            if (!locally_descending || !is_diff_gradual)
            {
                if (!dampened)
                {
                    std::vector<int> temp_levels_1 = levels;
                    std::vector<int> temp_levels_2 = levels;

                    temp_levels_1.erase(temp_levels_1.begin() + i + 1);
                    temp_levels_2.erase(temp_levels_2.begin() + i);

                    return is_safe(temp_levels_1, true) || is_safe(temp_levels_2, true);
                }

                return false;
            }
        }
    }

    return true;
}

int day02_2(const std::string &file_path)
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

        while (iss >> level) levels.push_back(level);

        if (is_safe(levels)) counter++;
    }

    file.close();

    return counter;
}
