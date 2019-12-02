#include "Student.h"

vector<int> Student::_ids;

//Конструктор с параметрами
Student::Student(char* name, int course, int group,int recordNum) : _recordNum(recordNum), _id(_randId()), _name(name), _course(course), _group(group){}
//Конструктор копирования
Student::Student(const Student &student): _id(_randId()), _name(student._name), _course(student._course), _group(student._group), _recordNum(student._recordNum){}

int Student::_randId(){
    int id;
    while(true){
        id = rand() % 10000;
        bool isUnic = true;
        for(int i : _ids){
            if(id == i){
                isUnic = false;
                break;
            }
        }
        if(isUnic){
            _ids.push_back(id);
            return id;
        }
    }
}

int Student::getId(){
    return _id;
}
char* Student::getName(){
    return _name;
}
int Student::getCourse(){
    return _course;
}
int Student::getGroup(){
    return _group;
}
const int Student::getRecordNum(){
    return _recordNum;
}

void Student::setName(char* name){
    _name = name;
}
void Student::setCourse(int course){
    _course = course;
}
void Student::setGroup(int group){
    _group = group;
}

double Student::calculateAverageMark() {
    return 0;
}

ostream &operator<< (ostream &out, const Student &s){
    out<<"Name: "<< s._name<< ", course: "<< s._course<< ", group: " << s._group<< ", record number: " << s._recordNum;
    return out;
}