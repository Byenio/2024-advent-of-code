#ifndef DAY01_H
#define DAY01_H

#include <string>
#include <vector>

struct MinimalElement
{
    int value;
    int index;
};

MinimalElement get_minimal_element(const std::vector<int> &v, int index);

int day01_1(const std::string &file_path);

#endif //DAY01_H
