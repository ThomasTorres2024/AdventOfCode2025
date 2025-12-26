/**
 * @brief Advent of Code Day 5
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

bool modifyBounds(std::vector<std::pair<size_t, size_t>> *ranges, size_t r1, size_t r2);

int main(int argc, char *argv[])
{
    // problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief Modifies the bounds of some interval and then returns if the bounds were modified during the runtime or not.
 * @param[in] ranges - The list of ranges
 * @param[in] r1 - New left entry
 * @param[in] r2 - New right entry
 */
bool modifyBounds(std::vector<std::pair<size_t, size_t>> *ranges, size_t r1, size_t r2)
{
    bool boundsModified = false;

    for (size_t i = 0; i < ranges->size(); i++)
    {

        auto r = ranges->at(i);
        if (r1 != r.first && r2 != r.second)
        {
            // case: a |  |
            if (r1 <= r.first && r2 > r.first)
            {

                ranges->at(i).first = r1;
                // case: a | | b
                if (r2 > r.second)
                {
                    ranges->at(i).second = r2;
                }
                boundsModified = true;
                break;
            }
            // case: | a | b
            else if (r1 >= r.first && r1 <= r.second && r2 > r.second)
            {
                ranges->at(i).second = r2;
                boundsModified = true;
                break;
            }
        }
    }

    return boundsModified;
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

    std::vector<std::pair<size_t, size_t>> ranges;
    std::vector<size_t> valsToCheck;

    bool readRanges = true;

    // read data by line
    while (std::getline(dataFile, line))
    {

        if (readRanges && line.size() == 1)
        {
            readRanges = false;
        }
        else if (readRanges)
        {
            // parse line
            std::string first, second;
            std::istringstream sstream(line);

            // parse first and second
            std::getline(sstream, first, '-');
            std::getline(sstream, second, '-');

            ranges.push_back(std::make_pair(std::stoul(first), std::stoul(second)));
        }
        else
        {
            valsToCheck.push_back(std::stoul(line));
        }
    }

    size_t valid = 0;

    // for(auto v : valsToCheck){
    //     std::cout <<v<<",";
    // }
    // std::cout<<"\n";

    for (auto v : valsToCheck)
    {
        for (auto range : ranges)
        {
            if (range.first <= v && v <= range.second)
            {

                valid++;
                break;
            }
        }
    }

    std::cout << "Count of valid: " << valid << "\n";

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

    std::vector<std::pair<size_t, size_t>> ranges;

    // read data by line
    while (std::getline(dataFile, line))
    {

        if (line.size() != 1)
        {
            std::string first, second;
            std::istringstream sstream(line);

            // parse first and second
            std::getline(sstream, first, '-');
            std::getline(sstream, second, '-');

            size_t r1 = std::stoul(first);
            size_t r2 = std::stoul(second);

            ranges.push_back(std::make_pair(r1, r2));
        }
        else
        {
            break;
        }
    }

    //sort so we only need to deal with the sec value 
    std::sort(ranges.begin(), ranges.end());

    // condense ranges here
    auto curr = ranges.at(0);

    //make new list with all valid pairs 
    std::vector<std::pair<size_t, size_t>> validRanges;

    //eliminate any overlap in the pairs 
    for (size_t i = 1; i < ranges.size(); i++)
    {
        auto compare = ranges.at(i);

        if (curr.second >= compare.first)
        {
            if (compare.second >= curr.second)
            {
                curr.second = compare.second;
            }
        }
        else
        {
            validRanges.push_back(curr);
            curr = ranges.at(i);

        }
    }
    validRanges.push_back(curr); 

    size_t uniquePositions = 0;

    for (auto r : validRanges)
    {
        uniquePositions += (r.second - r.first + 1);
        // std::cout << r.first << "," << r.second << "\n";
    }

    std::cout << "Total: " << uniquePositions << "\n";

    dataFile.close();
}
