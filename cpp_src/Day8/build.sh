#Author Thomas Torres
#Date 12/24/25
#Advent of Code CPP Winter 2028 Problem 8

root=cpp_src/Day8
output_name=$root/p8.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p8.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"