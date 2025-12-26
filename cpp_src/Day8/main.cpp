/**
 * @brief Advent of Code Day 8
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
#include <unordered_map>
#include <set> // for unique elements
#include <limits>

void problem1(int argc, char *argv[]);

void problem2(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    problem1(argc, argv);
    // problem2(argc, argv);

    return 0;
}

/**
 * Represents a vector with 3 components
 */
struct vec3
{
    int x;
    int y;
    int z;

    vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vec3(int x1, int y1, int z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }

    bool operator==(const vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

int dist(vec3 *a, vec3 *b);

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

    std::vector<vec3> vecs;

    while (std::getline(dataFile, line))
    {
        std::istringstream sstream(line);
        // std::cout << line << "\n";

        // do cast and capture values
        std::string first, second, third;

        std::getline(sstream, first, ',');
        std::getline(sstream, second, ',');
        std::getline(sstream, third, ',');

        vecs.push_back({std::stoi(first), std::stoi(second), std::stoi(third)});
    }

    std::vector<int> correspondingIndeces(vecs.size());

    // keep record of dists
    std::vector<std::pair<int, std::pair<size_t, size_t>>> shortestDists;
    // std::set<std::pair<int, std::pair<size_t, size_t>>> shortestDistsSet;

    // calculate vectors that minimize dist
    for (size_t i = 0; i < vecs.size(); i++)
    {
        auto vec1 = vecs.at(i);
        size_t minIdx = i;
        int minVal = std::numeric_limits<int>::max();
        for (size_t j = 0; j < vecs.size(); j++)
        {

            // std::cout<<dist(&vec1, &vecs.at(j))<<"\n";

            if (i != j && dist(&vec1, &vecs.at(j)) < minVal)
            {
                minVal = dist(&vec1, &vecs.at(j));
                minIdx = j;
            }
        }
        correspondingIndeces.at(i) = minIdx;
        shortestDists.push_back(std::make_pair(minVal, std::make_pair(i, minIdx)));
        // std::cout<<minVal<<"\n";
        // std::cout<<"I: " << i << ", J: " << minIdx <<"\n";
        // std::cout << vecs.at(minIdx).x << "," << vecs.at(minIdx).y << "," << vecs.at(minIdx).z << "\n";
        // std::cout<<"----------------------------------------------\n";
    }

    // for(auto v : vecToMin){
    //     std::cout<<v.first.x <<","<<v.first.y <<","<<v.first.z <<":"<<
    // }

    // sort distances
    std::sort(shortestDists.begin(), shortestDists.end());

    // for (auto idxAndVecs : shortestDists)
    // {
    //     std::cout << idxAndVecs.first << "\n";

    //     std::cout<<"I: " << idxAndVecs.second.first << ", J: " << idxAndVecs.second.second <<"\n";

    //     auto v = vecs.at(idxAndVecs.second.first);
    //     auto p = vecs.at(idxAndVecs.second.second);
    //     std::string hashableVec = std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z);
    //     std::string hashableShortest = std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);

    //     std::cout << hashableVec << "\n";
    //     std::cout << hashableShortest << "\n";
    //     std::cout << "-------------\n";
    // }


    size_t ITERATIONS = 10;
    std::set<std::set<std::string>> circuits;
    for(size_t j = 0; j < vecs.size();j++){
        auto v = vecs.at(j);
        circuits.insert({std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z)});
    }

    size_t i = 0;
    while (ITERATIONS > 0)
    {

        std::cout << i << "\n";

        auto idxAndVecs = shortestDists.at(i);

        auto v = vecs.at(idxAndVecs.second.first);
        auto p = vecs.at(idxAndVecs.second.second);

        std::string hashableVec = std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z);
        std::string hashableShortest = std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);
        bool notFound = true;

        // std::cout << idxAndVecs.first << "\n";
        // std::cout << hashableVec << "\n";
        // std::cout << hashableShortest << "\n";
        // std::cout << "-------------\n";

        for(auto circuit : circuits){
            if(circuit.find())
        }

        for (size_t j = 0; j < circuits.size(); j++)
        {
            // case add second
            auto circuit = circuits.at(j);
            if (circuit.find(hashableVec) != circuit.end() && circuit.find(hashableShortest) != circuit.end())
            {
                notFound = false;
                break;
            }
            else if (circuit.find(hashableVec) != circuit.end() || circuit.find(hashableShortest) != circuit.end())
            {
                circuits.at(j).insert(hashableVec);
                circuits.at(j).insert(hashableShortest);
                notFound = false;
                ITERATIONS--;
                break;
            }
        }
        // if no matches are found, then add it to a new circuit
        if (notFound)
        {
            circuits.push_back({hashableVec, hashableShortest});
            ITERATIONS--;
        }
        i++;
    }

    // size_t ITERATIONS = 10;
    // std::vector<std::set<std::string>> circuits;

    // size_t i = 0;
    // while (ITERATIONS > 0)
    // {

    //     std::cout << i << "\n";

    //     auto idxAndVecs = shortestDists.at(i);

    //     auto v = vecs.at(idxAndVecs.second.first);
    //     auto p = vecs.at(idxAndVecs.second.second);

    //     std::string hashableVec = std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z);
    //     std::string hashableShortest = std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);
    //     bool notFound = true;

    //     // std::cout << idxAndVecs.first << "\n";
    //     // std::cout << hashableVec << "\n";
    //     // std::cout << hashableShortest << "\n";
    //     // std::cout << "-------------\n";

    //     for (size_t j = 0; j < circuits.size(); j++)
    //     {
    //         // case add second
    //         auto circuit = circuits.at(j);
    //         if (circuit.find(hashableVec) != circuit.end() && circuit.find(hashableShortest) != circuit.end())
    //         {
    //             notFound = false;
    //             break;
    //         }
    //         else if (circuit.find(hashableVec) != circuit.end() || circuit.find(hashableShortest) != circuit.end())
    //         {
    //             circuits.at(j).insert(hashableVec);
    //             circuits.at(j).insert(hashableShortest);
    //             notFound = false;
    //             ITERATIONS--;
    //             break;
    //         }
    //     }
    //     // if no matches are found, then add it to a new circuit
    //     if (notFound)
    //     {
    //         circuits.push_back({hashableVec, hashableShortest});
    //         ITERATIONS--;
    //     }
    //     i++;
    // }

    // get list of circuit sizes and sort them
    std::vector<int> circuitSizes;
    for (auto c : circuits)
    {
        circuitSizes.push_back(c.size());
    }

    std::sort(circuitSizes.begin(), circuitSizes.end());

    for (size_t i = 0; i < circuitSizes.size(); i++)
    {
        std::cout << i << ".)" << circuitSizes.at(i) << "\n";
    }

    // int total = 0;
    std::size_t len = circuitSizes.size();
    std::cout << "Top 3 Circuits Products: " << circuitSizes.at(len - 3) * circuitSizes.at(len - 2) * circuitSizes.at(len - 1) << "\n";

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
    // // read in data from the file
    // std::string file_name(argv[1]);
    // std::ifstream dataFile(file_name);

    // // read in data in file as a large line
    // std::string line;

    // std::vector<std::string> data;
    // std::set<std::string> splitLocations;

    // // read data by line
    // int rowCtr = 0;
    // std::pair<int, int> start;
    // while (std::getline(dataFile, line))
    // {
    //     data.push_back(line);

    //     // std::cout<<line<<"\n";

    //     // iterate over line, if we find a beam splitter add it to list of beam splitters
    //     // if we find starting pos, add it too
    //     for (int colCtr = 0; colCtr < line.size(); colCtr++)
    //     {
    //         if (line.at(colCtr) == '^')
    //         {
    //             splitLocations.insert(std::to_string(rowCtr) + "," + std::to_string(colCtr));
    //         }
    //         else if (line.at(colCtr) == 'S')
    //         {
    //             start = std::make_pair(rowCtr, colCtr);
    //         }
    //     }

    //     // we don't know row size, so increment counter.
    //     rowCtr++;
    // }

    // std::map<std::string,int> seen;
    // int total = dfsP2(0, rowCtr, start.second, &splitLocations, data.at(0).size(),&seen);

    // std::cout << "Total of Beams Split : " << total << "\n";

    // dataFile.close();
}

/**
 * @brief Euclidean dist between 2 different vectors
 * @param[in] a - vec 1
 * @param[in] b - vec 2
 * @return euclidean dist between both vectors
 */
int dist(vec3 *a, vec3 *b)
{
    return sqrt(std::pow((a->x - b->x), 2) + std::pow((a->y - b->y), 2) + std::pow((a->z - b->z), 2));
}