#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

int day03_2(const std::string &file_path)
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

    std::regex full_regex(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    std::regex mul_regex(R"(mul\((\d+),(\d+)\))");
    std::regex do_regex(R"(do\(\))");
    std::regex dont_regex(R"(don't\(\))");
    std::smatch match;

    bool enabled = true;
    int total_sum = 0;

    std::string::const_iterator it = data.cbegin();

    while (
        std::regex_search(it, data.cend(), match, full_regex)
    )
    {
        if (std::regex_match(match.str(), do_regex)) enabled = true;

        if (std::regex_match(match.str(), dont_regex)) enabled = false;

        if (std::regex_match(match.str(), mul_regex) && enabled)
        {
            int num1 = std::stoi(match[1]);
            int num2 = std::stoi(match[2]);
            total_sum += num1 * num2;
        }

        it = match.suffix().first;
    }

    file.close();

    return total_sum;
}
