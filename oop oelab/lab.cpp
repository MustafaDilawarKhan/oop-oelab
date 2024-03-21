#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<fstream>
using namespace std;

class Course;

class Student {
public:
    string studentID;
    string name;
    string email;
     vector<string> coursesEnrolled;     // Track enrolled courses
    void enrollCourse(Course* course);
     void dropCourse(Course* course);
    void viewCourses();
};
//enrollment
void Student::enrollCourse(Course* course) {
    if (find(coursesEnrolled.begin(), coursesEnrolled.end(), course) != coursesEnrolled.end()) {
        cout << "Student " << name << " is already enrolled in course " << course->courseName << endl;
    } else {
        course->addStudent(this);
        coursesEnrolled.push_back(course);
        cout << "Student " << name << " enrolled in course " << course->courseName << endl;
    }
}
//opt out of course
void Student::dropCourse(Course* course) {
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
    if (it != coursesEnrolled.end()) {
        course->removeStudent(this);
        coursesEnrolled.erase(it);
        cout << "Student " << name << " dropped from course " << course->courseName << endl;
    } else {
        cout << "Student " << name << " is not enrolled in course " << course->courseName << endl;
    }
}

//display courses
void Student::viewCourses() {
  cout << "Courses enrolled by student " << name << ":" << endl;
    for (Course* course : coursesEnrolled) {
        cout << "Code: " << course->courseCode << ", Name: " << course->courseName << endl;
    }
}


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
    void addStudent(Student* student);
    void removeStudent(Student* student);
void viewStudents();
};

void Course::addStudent(Student* student) {
    if (studentsEnrolled.size() < maxCapacity) {
        studentsEnrolled.push_back(student);
        cout << "Student " << student->name << " added to course " << courseName <<endl;
    } else {
        cout << "Course " << courseName << " is full." << endl;
    }
}

void Course::removeStudent(Student* student) {
    studentsEnrolled.erase(remove(studentsEnrolled.begin(), studentsEnrolled.end(), student), studentsEnrolled.end());
    cout << "Student " << student->name << " removed from course " << courseName << endl;
}

void Course::viewStudents() {
    cout << "Students enrolled in course " << courseName << ":" << endl;
    for (Student* student : studentsEnrolled) {
        cout << "ID: " << student->studentID << ", Name: " << student->name << endl;
    }
}

int main() {


};
