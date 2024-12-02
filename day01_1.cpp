#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "include/day01_1.h"

MinimalElement get_minimal_element(const std::vector<int> &v)
{
    if (v.empty())
    {
        throw std::invalid_argument("empty vector");
    }

    MinimalElement result = {v.at(0), 0};

    for (int i = 1; i < v.size(); i++)
    {
        if (v.at(i) < result.value)
        {
            result.value = v.at(i);
            result.index = i;
        }
    }

    return result;
}

int day01_1(const std::string &file_path)
{
    std::fstream file(file_path, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Can't open file" << std::endl;
        return 1;
    }

    std::vector<int> vector1, vector2;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int value1, value2;

        if (iss >> value1 >> value2)
        {
            vector1.push_back(value1);
            vector2.push_back(value2);
        }
    }

    file.close();

    int diff_sum = 0;

    while (!vector1.empty())
    {
        MinimalElement min1 = get_minimal_element(vector1);
        MinimalElement min2 = get_minimal_element(vector2);

        int diff = abs(min1.value - min2.value);
        diff_sum += diff;

        vector1.erase(vector1.begin() + min1.index);
        vector2.erase(vector2.begin() + min2.index);
    }

    return diff_sum;
}
