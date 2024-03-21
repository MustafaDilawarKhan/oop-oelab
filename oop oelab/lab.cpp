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
    void assignCourse(Course* course);
    void viewCourses();
};

void Teacher::assignCourse(Course* course) {
    course->teacher = this;
    coursesTeaching.push_back(course);
}

void Teacher::removeCourse(Course* course) {
    course->teacher = nullptr;
    coursesTeaching.erase(remove(coursesTeaching.begin(), coursesTeaching.end(), course), coursesTeaching.end());
}

void Teacher::viewCourses() {
    for (Course* course : coursesTeaching) {
        cout << course->courseCode << " " << course->courseName << endl;
    }
}



class Course {
public:
    string courseCode;
    string courseName;
    Teacher* teacher;
    vector<Student*> studentsEnrolled;
    int maxCapacity = 50;
};

int main() {


};