
#include "Program.h"

int Program::Main(){
    Queue<Element<char>> queue;
    ReadInput("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input.txt",queue);
    Queue<Element<char>> queueAnsw = Conversion(queue);
    WriteCollection("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output.txt",queueAnsw);

    Tests();
    return 0;
}

void Program::ReadInput(string file, Queue<Element<char>> &queue){
    ifstream in(file);
    while (!in.eof()){
        char c;
        in>> c;
        Element<char> element(c);
        queue.push(element);
    }
    in.close();
}
Queue<Element<char>> Program::Conversion(Queue<Element<char>> &queue){
    PriorityQueue<Element<char>> priorityQueue;
    Queue<Element<char>> answ;
    while(!queue.isEmpty()){
        Element<char> element = queue.pop();
        if(element._value == '*'){
            if(!priorityQueue.isEmpty()){
                Element<char> element2 = priorityQueue.pull();
                answ.push(element2);
            }
        } else {
            priorityQueue.insert(element,element._value);
        }
    }
    return answ;
}
void Program::WriteCollection(string file, Queue<Element<char>> queue){
    ofstream out(file);
    while (!queue.isEmpty()){
        out<<queue.pop()._value;
    }
    out.close();
}

void Program::Tests(){
    Test("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input1.txt","D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output1.txt","SSSSGGDDSSSG");
    Test("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input2.txt","D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output2.txt","SGDSHFSHS");
    Test("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input3.txt","D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output3.txt","SGFDDSGD");
    Test("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input4.txt","D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output4.txt","SGDGSGDSGDS");
    Test("D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\input5.txt","D:\\4.Edu\\2.Prog\\2.Pract\\KR2\\output5.txt","WWWRJHRHRH");
}
void Program::Test(string inFile, string outFile,string trueStr){
    Queue<Element<char>> queue;
    ReadInput(inFile,queue);
    Queue<Element<char>> queueAnsw = Conversion(queue);
    WriteCollection(outFile,queueAnsw);
    ifstream in(outFile);
    string str;
    getline(in,str);
    assert(str == trueStr);
    in.close();
}
