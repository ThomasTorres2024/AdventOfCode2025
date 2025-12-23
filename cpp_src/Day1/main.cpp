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

// test function for problem 1, find pass by counting number of times we hit 0
void problem1(int argc, char *argv[]);

// test function for problem 2, find pass by counting total number of times we cross over 0
//void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief Solution to problem 1 in day 1, goes about task by restricting the range of the rotation to something within 0 <= r <=99,
 * and then determines if the resulting rotation should go to the upper portion, that is for l = r%100, if we should have pos = 100-l or pos = l.
 * If pos == 0 => password+=1
 *
 * @param[in] argc - Number of args
 * @param[in] argv - File name
 */
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
        instruction.second = instruction.second % 100;
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
            position = 100 - delta;
        }

        // std::cout << "Current Position: " << position << "\n";
        // std::cout << delta << "\n";

        if (position == 0)
        {
            res++;
        }
    }

    std::cout << "Resulting position is: " << res << "\n";

    dataFile.close();
}

/**
 * @brief Solution to problem 1 in day 1, goes about task by restricting the range of the rotation to something within 0 <= r <=99,
 * and then determines if the resulting rotation should go to the upper portion, that is for l = r%100, if we should have pos = 100-l or pos = l.
 * If pos == 0 => password+=1
 *
 * @param[in] argc - Number of args
 * @param[in] argv - File name
 */
void problem2(int agrv, char *argv[])
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
    bool initialPosZero = false;
    for (auto instruction : instructions)
    {
        // the number of times our answer is a multiple of 100 should be added to the total answer
        res += instruction.second / 100;
        // std::cout<<instruction.second / 100<<"\n";
        instruction.second = instruction.second % 100;

        // here we modify the original sol from 1 by changing the result to 1
        // results by 1

        if (position == 0)
        {
            initialPosZero = true;
        }
        else
        {
            initialPosZero = false;
        }

        if (instruction.first == 'L')
        {
            position -= instruction.second;
        }
        else
        {
            position += instruction.second;
        }

        delta = std::abs(position % 100);

        // rebalance bounds of the array, here if we are out of bounds => we needed to have
        // gone over 0 at least once, we can only go over once here because we already accounted for the
        // multiplies issue

        if (position > 99)
        {
            res++;
            position = delta;
        }
        else if (position < 0)
        {
            if (!initialPosZero)
            {
                res++;
            }

            position = 100 - delta;
        }
        else if (position == 0)
        {
            res++;
        }

        // ans inbetween 5850 > ans > 3252

        // std::cout << "Current Position: " << position << "\n";
        //  std::cout << delta << "\n";
    }

    std::cout << "Resulting position is: " << res << "\n";

    dataFile.close();
}