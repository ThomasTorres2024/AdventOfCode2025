/**
 * @brief Advent of Code Day 1
 * @date 12/22/25
 * @author Thomas Torres
 **/

#include <iostream> // see what happens
#include <string>
#include <vector>  //for storing things, potentially in the future
#include <fstream> //open up data file
#include <cmath>

// test function for problem 1 with locks
void problem1(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    problem1(argc, argv);

    return 0;
}

void problem1(int agrv, char *argv[])
{

    std::string file_name(argv[1]);
    std::ifstream dataFile(file_name);

    // process data file line by line
    std::string line;
    std::vector<std::pair<char, int>> instructions;

    // read data by line
    while (std::getline(dataFile, line))
    {
        char direction = line.at(0);

        // std::cout << line << "\n";

        // get the assosciated direction and position for each
        int position = std::stoi(line.substr(1));
        instructions.push_back(std::make_pair(direction, position));
    }

    // begin iteration
    int position = 50;
    int delta = 0;
    size_t res = 0;
    for (auto instruction : instructions)
    {
        instruction.second=instruction.second%100; 
        if (instruction.first == 'L')
        {
            position -= instruction.second;
        }
        else
        {
            position += instruction.second;
        }

        delta = std::abs(position % 100);

        // rebalance bounds of the array
        if (position > 99)
        {
            position = delta;
        }
        else if (position < 0)
        {
            position = 100-delta;
        }

        //std::cout << "Current Position: " << position << "\n";
        //std::cout << delta << "\n";

        if (position == 0)
        {
            res++;
        }
    }

    std::cout << "Resulting position is: " << res << "\n";

    dataFile.close();
}