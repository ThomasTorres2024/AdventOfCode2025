/**
 * @brief Advent of Code Day 9
 * @date 12/27/25
 * @author Thomas Torres
 **/

#include <iostream> // see what happens
#include <string>
#include <sstream>
#include <vector>  //for storing things, potentially in the future
#include <fstream> //open up data file
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set> // for unique elements
#include <limits>

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    //problem1(argc, argv);
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

    std::vector<std::pair<size_t,size_t>> pos; 

    while (std::getline(dataFile, line))
    {
        std::istringstream sstream(line);

        std::string row,col;

        std::getline(sstream, row, ',');
        std::getline(sstream, col, ',');

        //add to total list of cords 
        pos.push_back({std::stoul(row),std::stoul(col)});
    }
    size_t max = 0; 


    //simple grid search for largest area rectangle 
    //iterate over first idx 
    for(size_t i = 0; i < pos.size();i++){
        size_t first = pos.at(i).first;
        size_t second = pos.at(i).second;

        //now from 1st idx+1 to the end 
        for(size_t j = i+1; j < pos.size();j++){

            size_t first2 = pos.at(j).first;
            size_t second2 = pos.at(j).second;

            //determine max tri 
            size_t newRectangle =(std::max(first,first2)-std::min(first,first2)+1)*(std::max(second,second2)-std::min(second,second2)+1);
            if(newRectangle> max){
                max=newRectangle;
            }
        }
    }

    std::cout<<"Max Rectangle: " <<max<<"\n";
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

    std::vector<std::pair<size_t,size_t>> pos; 

    while (std::getline(dataFile, line))
    {
        std::istringstream sstream(line);

        std::string row,col;

        std::getline(sstream, row, ',');
        std::getline(sstream, col, ',');

        //add to total list of cords 
        pos.push_back({std::stoul(row),std::stoul(col)});
    }
    size_t max = 0; 


    //simple grid search for largest area rectangle 
    //iterate over first idx 
    for(size_t i = 0; i < pos.size();i++){
        size_t first = pos.at(i).first;
        size_t second = pos.at(i).second;

        //now from 1st idx+1 to the end 
        for(size_t j = i+1; j < pos.size();j++){

            size_t first2 = pos.at(j).first;
            size_t second2 = pos.at(j).second;

            //determine max tri 
            size_t newRectangle =(std::max(first,first2)-std::min(first,first2)+1)*(std::max(second,second2)-std::min(second,second2)+1);
            if(newRectangle> max){
                max=newRectangle;
            }
        }
    }

    std::cout<<"Max Rectangle: " <<max<<"\n";
    dataFile.close();
}
