/**
 * @brief Advent of Code Day 7
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
    problem1(argc, argv);
    // problem2(argc, argv);

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

    std::vector<std::string> data;
    std::set<std::string> splitLocations;

    // read data by line
    size_t rowCtr = 0;
    std::pair<size_t, size_t> start;
    while (std::getline(dataFile, line))
    {
        data.push_back(line);

        // std::cout<<line<<"\n";

        // iterate over line, if we find a beam splitter add it to list of beam splitters
        // if we find starting pos, add it too
        for (size_t colCtr = 0; colCtr < line.size(); colCtr++)
        {
            if (line.at(colCtr) == '^')
            {
                splitLocations.insert(std::to_string(rowCtr) + "," + std::to_string(colCtr));
            }
            else if (line.at(colCtr) == 'S')
            {
                start = std::make_pair(rowCtr, colCtr);
            }
        }

        // we don't know row size, so increment counter.
        rowCtr++;
    }

    size_t total = 0;

    std::set<size_t> pos;
    pos.insert(start.second);
    // go through each row
    for (size_t i = 0; i < rowCtr; i++)
    {
        std::set<size_t> nextPos;
        for (auto beam_col : pos)
        {
            // check if the split location is in the list of beam cols
            if (splitLocations.find(std::to_string(i) + "," + std::to_string(beam_col)) != splitLocations.end())
            {

                // add beam to the left
                if (beam_col != 0)
                {
                    nextPos.insert(beam_col - 1);
                }

                // add new beam to the right
                if (beam_col + 1 < data.at(0).size())
                {
                    nextPos.insert(beam_col + 1);
                }

                total++;
            }
            else
            {
                nextPos.insert(beam_col);
            }
        }
        // std::cout<<i<<".)"<< nextPos.size() << "\n";
        // total+=nextPos.size()-pos.size();
        pos = nextPos;
    }

    std::cout << "Total of Beams Split : " << total << "\n";

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
            total += subtotal;
        }
        else
        {
            size_t subtotal = 1;
            for (auto v : rowVals.at(i))
            {
                subtotal *= std::stoul(v);
            }
            total += subtotal;
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
