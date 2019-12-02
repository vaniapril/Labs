#ifndef LAB7_STUDENTAFTERSECONDSESSION_H
#define LAB7_STUDENTAFTERSECONDSESSION_H

#include "StudentAfterFirstSession.h"

class StudentAfterSecondSession : public StudentAfterFirstSession{
protected:
    vector<int> _secondSessionMarks;
    StudentAfterSecondSession();
public:
    StudentAfterSecondSession(char* name, int course, int group,int recordNum);
    StudentAfterSecondSession(const Student &student);
    StudentAfterSecondSession(const StudentAfterFirstSession &student);
    StudentAfterSecondSession(const StudentAfterSecondSession &student);

    vector<int> getSecondSessionMarks();
    void setSecondSessionMarks(int mark1,int mark2,int mark3,int mark4,int mark5);
    double calculateAverageMark() override;

    friend ostream &operator <<(ostream &out, const StudentAfterSecondSession &s);
};


#endif //LAB7_STUDENTAFTERSECONDSESSION_H
