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

// test function for problem 1, find total by splitting each string and comparing the half as a string
void problem1(int argc, char *argv[]);

// test function for problem 2, find total by comparing substrings equally (ugly solution, but it works i guess)
void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief Takes in each number, converts each number in range [a,b] into a string, and then takes the first
 * half and compares it against the second half. Equality => ID is invalid, so it's added to the sum of
 * all of the invalid values.
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
    std::string sentence;
    std::vector<std::pair<size_t, size_t>> rangeVals;

    // read in single line
    std::getline(dataFile, sentence);

    // prepare tokenization to parse string
    std::istringstream sstream(sentence);
    std::string token;
    std::vector<std::string> tokens;

    // parse string
    while (std::getline(sstream, token, ','))
    {
        std::string first, second;
        std::istringstream sstream(token);

        // parse first and second
        std::getline(sstream, first, '-');
        std::getline(sstream, second, '-');

        // for debug
        // std::cout<<first<<"-"<<second<<"\n";

        // add pair of first and second to
        rangeVals.push_back(std::make_pair(std::stoul(first), std::stoul(second)));
    }

    size_t invalid_sum = 0;

    // process range vals now for digits with duplicate entries
    for (auto vals : rangeVals)
    {
        size_t first = vals.first;
        size_t second = vals.second;

        // iterate over each bound
        for (size_t i = first; i <= second; i++)
        {
            std::string v = std::to_string(i);

            // we can only have the half-half string if it is evenly sized
            // otherwise we ignore
            if (v.size() % 2 == 0 && (v.substr(0, v.size() / 2) == v.substr(v.size() / 2, v.size())))
            {
                invalid_sum += i;
            }
        }
    }

    std::cout << "Invalid ID Sum: " << invalid_sum << "\n";

    dataFile.close();
}

/**
 * @brief Takes in each number, converts each number in range [a,b] into a string.
 * Takes substring of each string, and compares if the substring minus the actual string are equal.
 * Equality => ID is invalid, so it's added to the sum of all of the invalid values.
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
    std::string sentence;
    std::vector<std::pair<size_t, size_t>> rangeVals;

    // read in single line
    std::getline(dataFile, sentence);

    // prepare tokenization to parse string
    std::istringstream sstream(sentence);
    std::string token;
    std::vector<std::string> tokens;

    // parse string
    while (std::getline(sstream, token, ','))
    {
        std::string first, second;
        std::istringstream sstream(token);

        // parse first and second
        std::getline(sstream, first, '-');
        std::getline(sstream, second, '-');

        // for debug
        // std::cout<<first<<"-"<<second<<"\n";

        // add pair of first and second to
        rangeVals.push_back(std::make_pair(std::stoul(first), std::stoul(second)));
    }

    size_t invalid_sum = 0;

    // process range vals now for digits with duplicate entries
    for (auto vals : rangeVals)
    {
        size_t first = vals.first;
        size_t second = vals.second;


        // iterate over each bound
        for (size_t i = first; i <= second; i++)
        {
            std::string v = std::to_string(i);

            // we can only have the half-half string if it is evenly sized
            // otherwise we ignore
            bool isInvalid = false;
            std::string temp;

            //iterate over each valid substring (the substring is valid if we can 
            //obtain our temp number by appending it some integer number of times)
            for (size_t k = 1; k <= v.size() / 2; k++)
            {

                //check validity 
                if (v.size() % k == 0)
                {
                    temp = v.substr(0, k);
                    // std::cout<<"k: "<< k <<"\n";
                    std::string comparison;

                    //do appending 
                    for(size_t j = 0; j < v.size()/k; j++){
                        comparison+=temp;
                    }
                    
                    // std::cout<<comparison<<"-"<<i<<"="<<(std::stoul(comparison) - i)<<"\n";

                    //check equality of appended vs actual, if this is true => ID is invalid 
                    if (std::stoul(comparison) - i == 0)
                    {
                        isInvalid = true;
                        break;
                    }
                }
            }
            
            if (isInvalid)
            {
                invalid_sum += i;
                // std::cout<<i<<"\n";
            }

        }
    }

    std::cout << "Invalid ID Sum: " << invalid_sum << "\n";

    dataFile.close();
}