/**
 * @brief Advent of Code Day 3
 * @date 12/23/25
 * @author Thomas Torres
 **/

#include <iostream> // see what happens
#include <string>
#include <sstream>
#include <vector>  //for storing things, potentially in the future
#include <fstream> //open up data file
#include <cmath>

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    // problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief Does an O(n) search over each bank looking for the max, and then the second max. Once these are found, we have enough info
 * for the joltage of each bank, and the total joltage overall, which is our ans.
 *
 * @param[in] argc - Number of args
 * @param[in] argv - File name
 */
void problem1(int agrv, char *argv[])
{
    // read in data from the file
    std::string file_name(argv[1]);
    std::ifstream dataFile(file_name);

    // read in data in file as a large line
    std::string line;
    std::vector<std::string> banks;

    // read data by line
    while (std::getline(dataFile, line))
    {
        banks.push_back(line);
    }

    // parse each line
    size_t total = 0;
    for (auto bank : banks)
    {
        int max = 0;
        int secondHighest = 0;

        // iterate over ever number in the bank
        for (size_t i = 0; i < bank.size(); i++)
        {
            // ensure that the "highest" isn't at the edge
            if (bank.at(i) - '0' > max && (i != bank.size() - 2))
            {

                // change the max and second highest now that we know the order of things
                max = bank.at(i) - '0';
                secondHighest = 0;
            }
            else if (bank.at(i) - '0' > secondHighest)
            {
                secondHighest = bank.at(i) - '0';
            }
        }
        // std::cout<<max*10+secondHighest<<"\n";
        total += max * 10 + secondHighest;
    }

    std::cout << "Total Joltage: " << total << "\n";

    dataFile.close();
}

/**
 * @brief Does an O(n) search over each bank looking for the max, and then the second max. Once these are found, we have enough info
 * for the joltage of each bank, and the total joltage overall, which is our ans.
 *
 * @param[in] argc - Number of args
 * @param[in] argv - File name
 */
void problem2(int agrv, char *argv[])
{
    // read in data from the file
    std::string file_name(argv[1]);
    std::ifstream dataFile(file_name);

    // read in data in file as a large line
    std::string line;
    std::vector<std::string> banks;

    // read data by line
    while (std::getline(dataFile, line))
    {
        banks.push_back(line);
    }

    // parse each line
    size_t total = 0;
    for (auto bank : banks)
    {
        size_t start = 0;
        int remaining = 3;
        int max = bank.at(0) - '0';

        if (bank.at(1) - '0' > max)
        {
            max = bank.at(1) - '0';
            start = 1;
            remaining=2;
        }

        if (bank.at(2) - '0' > max)
        {
            max = bank.at(2) - '0';
            start = 2;
            remaining=1; 
        }

        // find max out of indeces 0,1,2 in bank

        // iterate over ever number in the bank
        for (size_t i = 0; i < bank.size(); i++)
        {
            // ensure that the "highest" isn't at the edge
            if (bank.at(i) - '0' > max && (i != bank.size() - 2))
            {

                // change the max and second highest now that we know the order of things
                max = bank.at(i) - '0';
                secondHighest = 0;
            }
            else if (bank.at(i) - '0' > secondHighest)
            {
                secondHighest = bank.at(i) - '0';
            }
        }
        // std::cout<<max*10+secondHighest<<"\n";
        total += max * 10 + secondHighest;
    }

    std::cout << "Total Joltage: " << total << "\n";

    dataFile.close();
}