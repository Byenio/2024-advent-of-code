#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int calculate_similarity_score(const std::vector<int> &vector1, const std::vector<int> &vector2)
{
    const int vector1_max = *std::ranges::max_element(vector1);
    const std::vector<int>::size_type vector_size = vector1.size();
    int arr[vector1_max + 1][2] = {{0}};

    for (int i = 0; i < vector_size; i++)
    {
        if (arr[vector1.at(i)][0] != 0)
        {
            arr[vector1.at(i)][1]++;
        }

        if (arr[vector1.at(i)][0] == 0)
        {
            int appearances = 0;
            for (int j = 0; j < vector_size; j++)
            {
                if (vector2[j] == vector1[i]) appearances++;
            }

            const int score = vector1[i] * appearances;

            arr[vector1.at(i)][0] = score;
            arr[vector1.at(i)][1] = 1;
        }
    }

    int total_score = 0;
    for (int i = 0; i <= vector1_max; i++)
    {
        total_score += arr[i][0] * arr[i][1];
    }

    return total_score;
}

int day01_2(const std::string &file_path)
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

    return calculate_similarity_score(vector1, vector2);
}
