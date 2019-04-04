#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

const float EPSINON = 0.0001;
std::vector<float> result;
int maxLength = 2;
unsigned int step = 0;

bool isSumZero()
{
    if(result.empty())
        return false;

    float sum = 0;
    for(auto n : result)
    {
        sum += n;
    }
    return (sum >= -EPSINON && sum <= EPSINON);
}

void writeResult(std::ofstream& output)
{
    output << "length:" << result.size() << std::endl;
    std::cout << "length:" << result.size() << std::endl;
    for(auto v : result)
    {
        output << std::fixed << std::setprecision(2) << v << ",";
        std::cout << std::fixed << std::setprecision(2) << v << ",";
    }
    output << std::endl;
    std::cout << std::endl;
}

void findSumZero(const std::vector<float>& in, int i, std::ofstream& output)
{
    step++;
    if(i < 0)
        return;

    if(maxLength < result.size())
    {
        if(isSumZero())
        {
            std::cout << "\nFind result in step " << step << std::endl;
            writeResult(output);
            maxLength = result.size();
        }
    }

    result.push_back(in[i]);
    findSumZero(in, i-1, output);
    result.pop_back();
    findSumZero(in, i-1, output);
}

bool readData(std::vector<float>& in)
{
    std::ifstream input;
    input.open("./trade_amount.txt", std::ios::in);
    if(!input.is_open())
    {
        std::cout << "ERROR: input.csv open failed!" << std::endl;
        return false;
    }

    std::string line;
    float value;
    std::cout << "Reading data from input.csv" << std::endl;
    while(getline(input, line))
    {
        while(std::find(line.begin(), line.end(), ',') != line.end())
        {
            line.erase(std::find(line.begin(), line.end(), ','));
        }
        std::stringstream ss(line);
        ss >> value;
        in.push_back(value);
    }
    input.close();

    for(auto v : in)
        std::cout << std::fixed << std::setprecision(2) << v << " ";
    std::cout << std::endl;
    std::cout << "Total=" << in.size() << std::endl;
    return true;
}

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        maxLength = std::atoi(argv[1]) - 1;
        std::cout << "Begin to check from " << maxLength + 1 << std::endl;
    }

    std::vector<float> in;
    if(readData(in))
    {
        std::ofstream output;
        output.open("./output.csv", std::ios::out);
        if(output.is_open())
        {
            findSumZero(in, in.size() - 1, output);
            output.close();
        }
        else
        {
            std::cout << "open output.csv failed!" << std::endl;
        }
    }
    return 0;
}

