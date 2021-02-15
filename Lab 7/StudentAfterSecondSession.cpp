#include "StudentAfterSecondSession.h"

//Конструктор с параметрами
StudentAfterSecondSession::StudentAfterSecondSession(char* name, int course, int group,int recordNum): StudentAfterFirstSession::StudentAfterFirstSession(name,course,group,recordNum){}
//Конструктор копирования из студента
StudentAfterSecondSession::StudentAfterSecondSession(const Student &student) : StudentAfterFirstSession::StudentAfterFirstSession(student){}
//Конструктор копиравния из студента первого курса
StudentAfterSecondSession::StudentAfterSecondSession(const StudentAfterFirstSession &student) : StudentAfterFirstSession(student){
    _firstSessionMarks = student.getFirstSessionMarks();
}
//Конструктор копиравния из студента второго курса
StudentAfterSecondSession::StudentAfterSecondSession(const StudentAfterSecondSession &student) : StudentAfterSecondSession(student._name, student._course, student._group,student._recordNum){
    _firstSessionMarks = student._firstSessionMarks;
    _secondSessionMarks = student._secondSessionMarks;
}

vector<int> StudentAfterSecondSession::getSecondSessionMarks(){
    return _secondSessionMarks;
}
void StudentAfterSecondSession::setSecondSessionMarks(int mark1,int mark2,int mark3,int mark4,int mark5){
    vector<int> newMarks;
    newMarks.push_back(mark1);
    newMarks.push_back(mark2);
    newMarks.push_back(mark3);
    newMarks.push_back(mark4);
    newMarks.push_back(mark5);
    _secondSessionMarks = newMarks;
}
double StudentAfterSecondSession::calculateAverageMark(){
    double n = 0;
    int num = 0;
    for(int i : _firstSessionMarks){
        n += i;
        num++;
    }
    for(int i : _secondSessionMarks){
        n += i;
        num++;
    }
    if(num != 0){
        n /= num;
    }
    return n;
}

ostream &operator <<(ostream &out, const StudentAfterSecondSession &s){
    out<<"Name: "<< s._name<< ", course: "<< s._course<< ", group: " << s._group<< ", record number: " << s._recordNum;
    out<<"marks: ";
    for(int i : s._firstSessionMarks){
        out<< i <<",";
    }
    for(int i : s._secondSessionMarks){
        out<< i <<",";
    }
    return out;
}