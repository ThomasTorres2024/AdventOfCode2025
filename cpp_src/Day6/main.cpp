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
    std::vector<std::string> data;
    std::vector<size_t> max;
    std::vector<std::string> ops;

    // read data by line
    bool parseOps = false;
    while (std::getline(dataFile, line))
    {

        // add to data matrix and get matrix of numeric vals
        std::istringstream sstream(line);
        data.push_back(line);

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

    // obtain col-wise max
    std::vector<size_t> maxes;

    // exterior loop for iterating through each col
    for (size_t j = 0; j < vals.at(0).size(); j++)
    {
        size_t currMax = 0;
        // go row wise now
        for (size_t i = 0; i < vals.size() - 1; i++)
        {

            // get new max idx
            if (vals.at(i).at(j).size() > currMax)
            {
                currMax = vals.at(i).at(j).size();
            }
        }
        maxes.push_back(currMax);
    }

    size_t prev = 0;

    std::vector<std::vector<std::string>> rowVals;

    // now for each col parse using
    //  exterior loop for iterating through each col
    for (size_t j = 0; j < ops.size(); j++)
    {
        // std::cout << j << "\n";
        size_t currMax = maxes.at(j);
        // go row wise now

        std::vector<std::string> rowNums(currMax, "");

        // values over the cols
        for (size_t k = 0; k < currMax; k++)
        {
            // values for each row
            for (size_t i = 0; i < vals.size() - 1; i++)
            {

                // std::cout << "curr max: " << currMax << "\n";
                // std::cout << data.at(i).at(prev + k) << "\n";
                // std::cout << i << "," << prev + k << "\n";
                // std::cout << "------------\n";

                if (data.at(i).at(prev + k) != ' ')
                {
                    rowNums.at(k) += data.at(i).at(prev + k);
                }
            }
        }

        // for(auto r : rowNums){
        //     std::cout<<r<<",";
        // }
        // std::cout<<"\n";

        // increment next starting position for the cols
        prev += currMax + 1;
        rowVals.push_back(rowNums);
    }

    size_t total = 0;
    for (size_t i = 0; i < ops.size(); i++)
    {
        std::string op = ops.at(i);

        if (op == "+")
        {
            size_t subtotal = 0;
            for (auto v : rowVals.at(i))
            {
                subtotal += std::stoul(v);
            }
            total+=subtotal;
        }
        else
        {
            size_t subtotal = 1;
            for (auto v : rowVals.at(i))
            {
                subtotal *= std::stoul(v);
            }
            total+=subtotal;
        }
    }

    // for (auto v : rowVals)
    // {
    //     for (auto a : v)
    //     {
    //         std::cout << a << ",";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "Total of Cephalapod Math P2: " << total << "\n";

    dataFile.close();
}
