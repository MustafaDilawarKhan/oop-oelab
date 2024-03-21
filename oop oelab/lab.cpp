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
    auto it = std::find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
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
    void removeCourse(Course* course);
};

void Teacher::assignCourse(Course* course) {
    course->teacher = this;
    coursesTeaching.push_back(course);
}

void Teacher::removeCourse(Course* course) {
    course->teacher = nullptr;
    coursesTeaching.erase(remove(coursesTeaching.begin(), coursesTeaching.end(), course), coursesTeaching.end());
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
