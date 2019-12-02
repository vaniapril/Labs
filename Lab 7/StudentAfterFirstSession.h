#ifndef LAB7_STUDENTAFTERFIRSTSESSION_H
#define LAB7_STUDENTAFTERFIRSTSESSION_H

#include "Student.h"

class StudentAfterFirstSession : public Student{
protected:
    StudentAfterFirstSession();
    vector<int> _firstSessionMarks;
public:
    StudentAfterFirstSession(char* name, int course, int group,int recordNum);
    StudentAfterFirstSession(const StudentAfterFirstSession &student);
    StudentAfterFirstSession(const Student &student);

    vector<int> getFirstSessionMarks() const;
    void setFirstSessionMarks(int mark1,int mark2,int mark3,int mark4);
    double calculateAverageMark() override;

    friend ostream &operator <<(ostream &out, const StudentAfterFirstSession &s);
};


#endif //LAB7_STUDENTAFTERFIRSTSESSION_H
