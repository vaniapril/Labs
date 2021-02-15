#include "StudentAfterFirstSession.h"

//Конструктор с параметрами
StudentAfterFirstSession::StudentAfterFirstSession(char* name, int course, int group,int recordNum): Student::Student(name,course,group,recordNum){}
//Конструктор копирования из студента
StudentAfterFirstSession::StudentAfterFirstSession(const Student &student) : Student::Student(student){}
//Конструктор копиравния из студента первого курса
StudentAfterFirstSession::StudentAfterFirstSession(const StudentAfterFirstSession &student):StudentAfterFirstSession(student._name,student._course,student._group,student._recordNum){
    _firstSessionMarks = student._firstSessionMarks;
}

vector<int> StudentAfterFirstSession::getFirstSessionMarks() const{
    return _firstSessionMarks;
}
void StudentAfterFirstSession::setFirstSessionMarks(int mark1,int mark2,int mark3,int mark4){
    vector<int> newMarks;
    newMarks.push_back(mark1);
    newMarks.push_back(mark2);
    newMarks.push_back(mark3);
    newMarks.push_back(mark4);
    _firstSessionMarks = newMarks;
}
double StudentAfterFirstSession::calculateAverageMark(){
    double n = 0;
    int num = 0;
    for(int i : _firstSessionMarks){
        n += i;
        num++;
    }
    if(num != 0){
        n /= num;
    }
    return n;
}

ostream &operator <<(ostream &out, const StudentAfterFirstSession &s){
    out<<"Name: "<< s._name<< ", course: "<< s._course<< ", group: " << s._group<< ", record number: " << s._recordNum;
    out<<", marks: ";
    for(int i : s._firstSessionMarks){
        out<< i <<",";
    }
    return out;
}