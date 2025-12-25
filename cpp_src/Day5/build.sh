#Author Thomas Torres
#Date 12/24/25 
#Advent of Code CPP Winter 2025 Problem 5

root=cpp_src/Day5
output_name=$root/p5.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p5.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"