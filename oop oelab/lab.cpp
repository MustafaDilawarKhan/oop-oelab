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
    void readFromFile(ifstream &infile);
    void writeToFile(ofstream &outfile); 
};

//enrollment
void Student::enrollCourse(Course* course) {
    if (find(coursesEnrolled.begin(), coursesEnrolled.end(), course->courseCode) != coursesEnrolled.end()) {
        cout << "Student " << name << " is already enrolled in course " << course->courseName << endl;
    } else {
        course->addStudent(this);
         coursesEnrolled.push_back(course->courseCode);
        cout << "Student " << name << " enrolled in course " << course->courseName << endl;
    }
}
//opt out of course
void Student::dropCourse(Course* course) {
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course->courseCode);
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
    for (const string &courseCode : coursesEnrolled) {
        cout << "Code: " << courseCode << ", Name: " << getCourseName(courseCode) << endl;
    }
}

void Student::readFromFile(ifstream &infile) {
    if (!infile.is_open()) {
        cerr << "Error: File not open for reading." << endl;
        return;
    }
    infile >> studentID >> name >> email;
    string courseCode;
    while (infile >> courseCode) {
        coursesEnrolled.push_back(courseCode);
    }
}

void Student::writeToFile(ofstream &outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << studentID << " " << name << " " << email;
    for (const string &courseCode : coursesEnrolled) {
        outfile << " " << courseCode;
    }
    outfile << endl;
}


class Teacher {
public:
    string teacherID;
    string name;
    string email;
    void assignCourse(Course* course);
    vector<string> coursesTeaching; // Track assigned courses
    void viewCourses();
    void readFromFile(ifstream &infile);
    void writeToFile(ofstream &outfile);
};

void Teacher::assignCourse(Course* course) {
    course->teacherID = teacherID;
    coursesTeaching.push_back(course->courseCode);
}

void Teacher::removeCourse(Course* course) {
    course->teacherID = "";
    coursesTeaching.erase(remove(coursesTeaching.begin(), coursesTeaching.end(), course->courseCode), coursesTeaching.end());
}

void Teacher::viewCourses() {
    cout << "Courses assigned to teacher " << name << ":" << endl;
    for (const string &courseCode : coursesTeaching) {
        cout << "Code: " << courseCode << ", Name: " << getCourseName(courseCode) << endl;
    
    }
}


void Teacher::readFromFile(ifstream &infile) {
    if (!infile.is_open()) {
        cerr << "Error: File not open for reading." << endl;
        return;
    }
    infile >> teacherID >> name >> email;
    string courseCode;
    while (infile >> courseCode) {
        coursesTeaching.push_back(courseCode);
    }
}

void Teacher::writeToFile(ofstream &outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << teacherID << " " << name << " " << email;
    for (const string &courseCode : coursesTeaching) {
        outfile << " " << courseCode;
    }
    outfile << endl;
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
     void readFromFile(ifstream &infile);
    void writeToFile(ofstream &outfile);
};

void Course::addStudent(Student* student) {
    if (studentsEnrolled.size() < maxCapacity) {
        studentsEnrolled.push_back(student->studentID);
        cout << "Student " << student->name << " added to course " << courseName <<endl;
    } else {
        cout << "Course " << courseName << " is full." << endl;
    }
}

void Course::removeStudent(Student* student) {
    studentsEnrolled.erase(remove(studentsEnrolled.begin(), studentsEnrolled.end(), student->studentID), studentsEnrolled.end());
    cout << "Student " << student->name << " removed from course " << courseName << endl;
}

void Course::viewStudents() {
    cout << "Students enrolled in course " << courseName << ":" << endl;
    for (const string &studentID : studentsEnrolled) {
        cout << "ID: " << studentID << ", Name: " << getStudentName(studentID) << endl;
    }
}

void Course::readFromFile(ifstream &infile) {
    if (!infile.is_open()) {
        cerr << "Error: File not open for reading." << endl;
        return;
    }
    infile >> courseCode >> courseName >> teacherID;
    string studentID;

while (infile >> studentID) {
        studentsEnrolled.push_back(studentID);
    }
}

void Course::writeToFile(ofstream &outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << courseCode << " " << courseName << " " << teacherID;
    for (const string &studentID : studentsEnrolled) {
        outfile << " " << studentID;
    }
    outfile << endl;
}

int main() {


};
