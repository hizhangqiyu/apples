#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

std::vector<float> result;
int maxLength = 0;
bool isSumZero(const std::vector<float>& v)
{
    float sum = 0;
    for(auto n : v)
    {
        sum += n;
    }
    return (sum == 0 && !v.empty());
}

void findSumZero(const std::vector<float>& in, float i)
{
    if(i < 0)
        return;

    if(isSumZero(result))
    {
        if(maxLength < result.size())
        {
            std::cout << "length:" << result.size() << std::endl;
            for(auto v : result)
                std::cout << std::fixed << std::setprecision(2) << v << ",";
            std::cout << std::endl;
            maxLength = result.size();
        }
    }
    result.push_back(in[i]);
    findSumZero(in, i-1);
    result.pop_back();
    findSumZero(in, i-1);
}

int main()
{
    std::ifstream input;
    input.open("input.csv", std::ios::in);
    std::string line;
    float value;
    std::vector<float> in;
    while(getline(input, line))
    {
        std::stringstream ss(line);
        ss >> value;
        in.push_back(value);
    }
    for(auto v : in)
        std::cout << std::fixed << std::setprecision(2) << v << " ";
    std::cout << std::endl;
    std::cout << "Total=" << in.size() << std::endl;
    findSumZero(in, in.size() - 1);

//    std::ofstream output;
//    output.open("output.csv", std::ios::out);

    return 0;
}
