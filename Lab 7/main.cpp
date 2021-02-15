#include <iostream>
#include "Student.h"
#include "StudentAfterFirstSession.h"
#include "StudentAfterSecondSession.h"

using namespace std;

vector<Student*> randomStudentPointers(){
    vector<Student*> studentPointers;
    int n1 = rand()%70 + 30;
    for(int i = 0; i < n1; i++){
        Student* student = new Student("Student",1,rand()%10 + 1,rand()%10000);
        studentPointers.push_back(student);
    }

    int n2 = rand()%50 + 30;
    for(int i = 0; i < n2; i++){
        StudentAfterFirstSession* student = new StudentAfterFirstSession("Student",1,rand()%10 + 1,rand()%10000);
        student->setFirstSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        studentPointers.push_back(student);
    }
    for(int i = 0; i < 15; i++){
        StudentAfterFirstSession* student = new StudentAfterFirstSession(*studentPointers[i]);
        student->setFirstSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        studentPointers.push_back(student);
    }
    int n3 = rand()%40 + 30;
    for(int i = 0; i < n3; i++){
        StudentAfterSecondSession* student = new StudentAfterSecondSession("Student",1,rand()%10 + 1,rand()%10000);
        student->setFirstSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        student->setSecondSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        studentPointers.push_back(student);
    }
    for(int i = 15; i < 30; i++){
        StudentAfterSecondSession* student = new StudentAfterSecondSession(*studentPointers[i]);
        student->setFirstSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        student->setSecondSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        studentPointers.push_back(student);
    }
    for(int i = n1; i < n1 + 15; i++){
        StudentAfterSecondSession* student = new StudentAfterSecondSession(*studentPointers[i]);
        student->setSecondSessionMarks(rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2,rand()%9 + 2);
        studentPointers.push_back(student);
    }
    return studentPointers;
}

double calculateAverageGroupMark(int group, vector<Student*> students) {
    double n = 0;
    int num = 0;
    for(Student* i : students){
        if(i->getGroup() == group){
            double averageMark = i->calculateAverageMark();
            if(averageMark != 0){
                n += averageMark;
                num++;
            }
        }
    }
    if(num != 0){
        n /= num;
    }
    return n;
}
double calculateAllAverageMark(vector<Student*> students){
    double n = 0;
    int num = 0;
    for(Student* i : students){
        double averageMark = i->calculateAverageMark();
        if(averageMark != 0){
            n += averageMark;
            num++;
        }
    }
    if(num != 0){
        n /= num;
    }
    return n;
}

int main() {
    vector<Student*> studentPointers = randomStudentPointers();

    for(int i = 1; i <= 10;i++){
        cout<<"Average mark group "<< i<<": " << calculateAverageGroupMark(i,studentPointers)<<'\n';
    }

    cout<<"Average mark All: " << calculateAllAverageMark(studentPointers)<<'\n';
    return 0;
}