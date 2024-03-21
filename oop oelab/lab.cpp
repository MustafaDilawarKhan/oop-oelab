#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
    string studentID;
    string name;
    string email;
};

class Teacher {
public:
    string teacherID;
    string name;
    string email;
};

class Course {
public:
    string courseCode;
    string courseName;
    Teacher* teacher;
    vector<Student*> studentsEnrolled;
    int maxCapacity = 50;
    void assignCourse(Course* course);
};

void Teacher::assignCourse(Course* course) {
    course->teacher = this;
    coursesTeaching.push_back(course);
}


int main() {


};