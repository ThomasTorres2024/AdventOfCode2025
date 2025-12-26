#Author Thomas Torres
#Date 12/24/25
#Advent of Code CPP Winter 2027 Problem 7

root=cpp_src/Day7
output_name=$root/p7.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p7.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"