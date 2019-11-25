#ifndef KR2_PROGRAM_H
#define KR2_PROGRAM_H

#include "Queue.h"
#include "PriorityQueue.h"
//#include "D:\4.Edu\2.Prog\2.Pract\KR2\Element.cpp"
#include "fstream"
#include "string"
#include "iostream"
#include "assert.h"

using namespace std;

class Program{
public:
    static int Main();

    static void ReadInput(string file, Queue<Element<char>> &queue);
    static Queue<Element<char>> Conversion(Queue<Element<char>> &queue);
    static void WriteCollection(string file, Queue<Element<char>> queue);
    static void Tests();
    static void Test(string inFile, string outFile,string trueStr);
};


#endif //KR2_PROGRAM_H
