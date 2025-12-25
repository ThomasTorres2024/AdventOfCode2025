/**
 * @brief Advent of Code Day 4
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

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

bool is_accessible(std::vector<std::string>* grid, size_t row, size_t col );

int main(int argc, char *argv[])
{
    //problem1(argc, argv);
    problem2(argc, argv);

    return 0;
}

/**
 * @brief Determines, for problem 1 of Day 4, if a square has less than 4 neighboring rolls.
 * @param[in] grid - The grid of values we will be using to determine neighbors 
 * @param[in] row - The row of the position checked 
 * @param[in] col - The col of the position checked  
 */
bool is_accessible(std::vector<std::string>* grid, int row, int col ){

    int candidatesRow[8]={row,  row  , row+1,row+1,row+1, row-1,row-1,row-1};
    int candidatesCol[8]={col-1,col+1, col-1,col , col+1, col-1,col+1,col};

    int near = 0; 

    // std::cout<<"At :"<<row<<","<<col<<"\n";

    for(int i = 0; i < 8; i++){
        int r = candidatesRow[i];
        int c = candidatesCol[i];
        
        // std::cout<<r<<","<<c<<"\n";

        if(  (r < (int) grid->size() &&  -1 < r && -1 < c && c < (int) grid->at(0).size()-1  ) && (grid->at(r).at(c)=='@') ){
            near++;
        }
    }

    return near<4;
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

    for(size_t i = 0; i < banks.size();i++){
        std::string bank = banks.at(i);
        // std::cout<<bank<<"\n";
        for(size_t j = 0; j < bank.size();j++){

            if(banks.at(i).at(j)=='@' && is_accessible(&banks, (int) i, (int) j)){
                total++; 
            }
        }
    }

    std::cout << "Total Accessible: " << total << "\n";

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

    std::vector<std::pair<int,int>> accessiblePos;

    // parse each line
    size_t total = 0;

    do{

        //begin by nullifying all accessible and then clear out all possible vals
        for(auto p : accessiblePos){
            banks.at(p.first).at(p.second)='.';
        }
        accessiblePos.clear();

        for(size_t i = 0; i < banks.size();i++){
            std::string bank = banks.at(i);
            // std::cout<<bank<<"\n";
            for(size_t j = 0; j < bank.size();j++){

                if(banks.at(i).at(j)=='@' && is_accessible(&banks, (int) i, (int) j)){
                    total++; 
                    accessiblePos.push_back(std::make_pair((int) i, (int) j));
                }
            }
        }

    } while(!accessiblePos.empty());


    std::cout << "Total Accessible: " << total << "\n";

    dataFile.close();
}