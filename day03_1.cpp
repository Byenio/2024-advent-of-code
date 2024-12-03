#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

int day03_1(const std::string &file_path)
{
    std::fstream file(file_path, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Can't open file" << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    std::regex mul_regex(R"(mul\((\d+),(\d+)\))");
    std::smatch match;

    int total_sum = 0;

    std::string::const_iterator it = data.cbegin();

    while (std::regex_search(it, data.cend(), match, mul_regex))
    {
        int num1 = std::stoi(match[1]);
        int num2 = std::stoi(match[2]);

        total_sum += num1 * num2;
        it = match.suffix().first;
    }

    file.close();

    return total_sum;
}
