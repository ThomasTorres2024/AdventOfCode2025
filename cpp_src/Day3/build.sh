#Author Thomas Torres
#Date 12/22/25 
#Advent of Code CPP Winter 2025 Problem 3

root=cpp_src/Day2
output_name=$root/p2.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p2.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"