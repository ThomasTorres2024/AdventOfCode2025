#Author Thomas Torres
#Date 12/22/25 
#Advent of Code CPP Winter 2025 Problem 1 

root=cpp_src/Day1
output_name=$root/p1.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p1.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"