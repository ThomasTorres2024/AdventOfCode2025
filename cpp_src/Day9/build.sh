#Author Thomas Torres
#Date 12/27/25
#Advent of Code CPP Winter 2029 Problem 9

root=cpp_src/Day9
output_name=$root/p9.exe 

#i like to clear my outputs 

echo "--------------------------------------------------------------"
g++ $root/main.cpp -Wall -std=c++23 -o $root/p9.exe 
echo Compiled file as $output_name
echo "--------------------------------------------------------------"