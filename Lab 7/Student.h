#ifndef LAB7_STUDENT_H
#define LAB7_STUDENT_H

#include <iostream>
#include <vector>
using namespace std;

class Student{
protected:
    static vector<int> _ids;
    const int _id;
    int _randId();
    char* _name;
    int _course;
    int _group;
    const int _recordNum;
    Student();
public:
    Student(char* name, int course, int group,int recordNum);
    Student(const Student &student);

    int getId();
    char* getName();
    int getCourse();
    int getGroup();
    const int getRecordNum();

    void setName(char* name);
    void setCourse(int course);
    void setGroup(int group);

    virtual double calculateAverageMark();

    friend ostream &operator <<(ostream &out, const Student &s);
};
#endif //LAB7_STUDENT_H
