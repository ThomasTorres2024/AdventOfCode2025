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
#include <map> 
#include <set> // for unique elements

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

size_t dfsP2(size_t i, size_t row_ctr, size_t curr_pos,
             std::set<std::string> *splitLocations, size_t rowLength,
             std::map<std::string,size_t>* seenIntermediateNotes);

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

    std::map<std::string,size_t> seen; 
    size_t total = dfsP2(0, rowCtr, start.second, &splitLocations, data.at(0).size(),&seen);

    std::cout << "Total of Beams Split : " << total << "\n";

    dataFile.close();
}

size_t dfsP2(size_t i, size_t row_ctr, size_t curr_pos,
             std::set<std::string> *splitLocations, size_t rowLength, std::map<std::string,size_t> *seen)
{

    std::string thisString=std::to_string(i)+","+std::to_string(curr_pos);

    // base case for completion
    if (i == row_ctr)
    {
        return 1;
    }
    else if(seen->find(thisString)!=seen->end()){
        
        return seen->at(thisString); 
    }
    else
    {
        size_t sum = 0;

        // check if the split location is in the list of beam cols
        if (splitLocations->find(std::to_string(i) + "," + std::to_string(curr_pos)) != splitLocations->end())
        {

            // left branch
            if (curr_pos != 0)
            {
                sum += dfsP2(i + 1, row_ctr, curr_pos - 1, splitLocations, rowLength,seen);
            }

            // right branch
            if (curr_pos + 1 < rowLength)
            {
                sum += dfsP2(i + 1, row_ctr, curr_pos + 1, splitLocations, rowLength,seen);
            }

            seen->insert({thisString, sum});  
            
        }
        // no splitter
        else
        {
            sum += dfsP2(i + 1, row_ctr, curr_pos, splitLocations, rowLength,seen);
            seen->insert({thisString, sum}); 
        }

        return sum;
    }
}
