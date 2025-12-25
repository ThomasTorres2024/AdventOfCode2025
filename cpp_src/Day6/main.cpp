/**
 * @brief Advent of Code Day 6
 * @date 12/24/25
 * @author Thomas Torres
 **/

#include <iostream> // see what happens
#include <string>
#include <sstream>
#include <vector>  //for storing things, potentially in the future
#include <fstream> //open up data file
#include <algorithm>
#include <cmath>
#include <set> // for unique elements

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    // problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief
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

    std::vector<std::vector<size_t>> vals;
    std::vector<std::string> ops;

    // read data by line
    bool parseOps = false;
    while (std::getline(dataFile, line))
    {

        // parse line
        std::string first, second;
        std::istringstream sstream(line);

        // std::cout << line << "\n";

        std::string s;

        std::vector<size_t> curr;

        while (sstream >> s)
        {
            if (s != "+" && s != "*")
            {
                curr.push_back(std::stoul(s));
            }
            else
            {
                parseOps = false;
                ops.push_back(s);
            }
        }

        if (!parseOps)
        {
            vals.push_back(curr);
        }
    }

    // do iteration
    size_t col = 0;
    // for (size_t i = 0; i < vals.size() ;i++){
    //     std::cout << vals.at(i).at(col) <<"\n";
    // }
    size_t total = 0;
    for (auto op : ops)
    {
        if (op == "+")
        {
            // std::cout<<vals.size()-1<<"\n";
            for (size_t i = 0; i < vals.size() - 1; i++)
            {
                total += vals.at(i).at(col);
                // std::cout << vals.at(i).at(col) <<"\n";
            }
        }
        else
        {
            // std::cout<<vals.size()-1<<"\n";
            size_t temp = 1;
            for (size_t i = 0; i < vals.size() - 1; i++)
            {
                temp *= vals.at(i).at(col);
                // std::cout << vals.at(i).at(col) <<"\n";
            }
            total += temp;
        }
        col++;
    }

    std::cout << "Total of Cephalapod Math: " << total << "\n";

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

    std::vector<std::vector<std::string>> vals; 
    std::vector<size_t> max;
    std::vector<std::string> ops;

    // read data by line
    bool parseOps = false;
    while (std::getline(dataFile, line))
    {

        std::istringstream sstream(line);

        // std::cout << line << "\n";

        std::string s;

        std::vector<std::string> curr;

        while (sstream >> s)
        {
            if (s != "+" && s != "*")
            {
                curr.push_back(s);
            }
            else
            {
                parseOps = false;
                ops.push_back(s);
            }
        }

        if (!parseOps)
        {
            vals.push_back(curr);
        }
    }

    // do iteration
    size_t col = 0;

    size_t total = 0;
    for (auto op : ops)
    {

        std::vector<std::vector<size_t>> toCut;

        // std::cout<<vals.size()-1<<"\n";
        for (size_t i = 0; i < vals.size() - 1; i++)
        {
            if(vals.at(i).at(col).size()<toCut.size())
            toCut.push_back(vals.at(i).at(col));
        }

        if (op == "+")
        {
            // std::cout<<vals.size()-1<<"\n";
            for (size_t i = 0; i < vals.size() - 1; i++)
            {
                total += vals.at(i).at(col);
                // std::cout << vals.at(i).at(col) <<"\n";
            }
        }
        else
        {
            // std::cout<<vals.size()-1<<"\n";
            size_t temp = 1;
            for (size_t i = 0; i < vals.size() - 1; i++)
            {
                temp *= vals.at(i).at(col);
                // std::cout << vals.at(i).at(col) <<"\n";
            }
            total += temp;
        }
        col++;
    }

    std::cout << "Total of Cephalapod Math: " << total << "\n";

    dataFile.close();
}
