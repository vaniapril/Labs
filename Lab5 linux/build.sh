#! /bin/bash
echo Make build directory.
mkdir build;
cd build;

#build
echo Build.
g++ -o run ../main.cpp -I../ -lpthread;
#run
echo Run.
./run;

#remove build directory
echo Remove build directory.
cd ../;
rm -r build;