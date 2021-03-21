#! /bin/bash
echo Make build directory.
mkdir build;
cd build;

#static
echo Make static library.
gcc -c ../Number/Number.cpp;
ar rvs Number.a Number.o;

#dynamic
echo Make dynamic library.
gcc -c ../Vector/Vector.cpp -I../Number/include -LNumber.a -shared -o Vector.so;

#demo
echo Run demo.
g++ -o demo ../Demo.cpp -I../Vector/include -I../Number/include Vector.so Number.a;
./demo;

#remove build directory
echo Remove build directory.
cd ../;
rm -r build;