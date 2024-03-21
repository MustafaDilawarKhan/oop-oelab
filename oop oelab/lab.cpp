#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class Teacher;
class Course;

class Student {
public:
    string studentID;
    string name;
    string email;
    vector<string> coursesEnrolled; // Track enrolled course codes

    // Methods
    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses();
    void readFromFile(ifstream& infile);
    void writeToFile(ofstream& outfile);
};

class Teacher {
public:
    string teacherID;
    string name;
    string email;
    vector<string> coursesTeaching; // Track assigned course codes

    // Methods
    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses();
    void readFromFile(ifstream& infile);
    void writeToFile(ofstream& outfile);
};

class Course {
public:
    string courseCode;
    string courseName;
    string teacherID; // To link to the teacher
    vector<string> studentsEnrolled; // Track enrolled student IDs
    int maxCapacity = 50;

    // Methods
    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents();
    void readFromFile(ifstream& infile);
    void writeToFile(ofstream& outfile);
};

// Global maps to store objects by ID
map<string, Student> studentsMap;
map<string, Teacher> teachersMap;
map<string, Course> coursesMap;

// Enrollment
void Student::enrollCourse(Course* course) {
    if (course->studentsEnrolled.size() < course->maxCapacity) {
        // Check if student is already enrolled
        if (find(coursesEnrolled.begin(), coursesEnrolled.end(), course->courseCode) != coursesEnrolled.end()) {
            cout << "Student " << name << " is already enrolled in course " << course->courseName << endl;
        }
        else {
            // Enroll student
            course->addStudent(this);
            coursesEnrolled.push_back(course->courseCode);
            cout << "Student " << name << " enrolled in course " << course->courseName << endl;
        }
    }
    else {
        cout << "Course " << course->courseName << " is full." << endl;
    }
}

// Opt out of course
void Student::dropCourse(Course* course) {
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course->courseCode);
    if (it != coursesEnrolled.end()) {
        course->removeStudent(this);
        coursesEnrolled.erase(it);
        cout << "Student " << name << " dropped from course " << course->courseName << endl;
    }
    else {
        cout << "Student " << name << " is not enrolled in course " << course->courseName << endl;
    }
}

// Display courses
void Student::viewCourses() {
    cout << "Courses enrolled by student " << name << ":" << endl;
    for (const string& courseCode : coursesEnrolled) {
        cout << "Code: " << courseCode << ", Name: " << coursesMap[courseCode].courseName << endl;
    }
}

// Assign course to teacher
void Teacher::assignCourse(Course* course) {
    course->teacherID = teacherID;
    coursesTeaching.push_back(course->courseCode);
}

// Remove assigned course
void Teacher::removeCourse(Course* course) {
    course->teacherID = "";
    coursesTeaching.erase(remove(coursesTeaching.begin(), coursesTeaching.end(), course->courseCode), coursesTeaching.end());
}

// Display courses taught by teacher
void Teacher::viewCourses() {
    cout << "Courses assigned to teacher " << name << ":" << endl;
    for (const string& courseCode : coursesTeaching) {
        cout << "Code: " << courseCode << ", Name: " << coursesMap[courseCode].courseName << endl;
    }
}

// Add student to course
void Course::addStudent(Student* student) {
    studentsEnrolled.push_back(student->studentID);
    cout << "Student " << student->name << " added to course " << courseName << endl;
}

// Remove student from course
void Course::removeStudent(Student* student) {
    studentsEnrolled.erase(remove(studentsEnrolled.begin(), studentsEnrolled.end(), student->studentID), studentsEnrolled.end());
    cout << "Student " << student->name << " removed from course " << courseName << endl;
}

// Display students enrolled in course
void Course::viewStudents() {
    cout << "Students enrolled in course " << courseName << ":" << endl;
    for (const string& studentID : studentsEnrolled) {
        cout << "ID: " << studentID << ", Name: " << studentsMap[studentID].name << endl;
    }
}

// Read student data from file
void Student::readFromFile(ifstream& infile) {
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

// Write student data to file
void Student::writeToFile(ofstream& outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << studentID << " " << name << " " << email;
    for (const string& courseCode : coursesEnrolled) {
        outfile << " " << courseCode;
    }
    outfile << endl;
}

// Read teacher data from file
void Teacher::readFromFile(ifstream& infile) {
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

// Write teacher data to file
void Teacher::writeToFile(ofstream& outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << teacherID << " " << name << " " << email;
    for (const string& courseCode : coursesTeaching) {
        outfile << " " << courseCode;
    }
    outfile << endl;
}

// Read course data from file
void Course::readFromFile(ifstream& infile) {
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

// Write course data to file
void Course::writeToFile(ofstream& outfile) {
    if (!outfile.is_open()) {
        cerr << "Error: File not open for writing." << endl;
        return;
    }
    outfile << courseCode << " " << courseName << " " << teacherID;
    for (const string& studentID : studentsEnrolled) {
        outfile << " " << studentID;
    }
    outfile << endl;
}

// Function to prompt user to enroll a student in a course
void enrollStudentInCourse() {
    string studentID;
    cout << "Enter student ID: ";
    cin >> studentID;

    // Check if student exists
    if (studentsMap.find(studentID) == studentsMap.end()) {
        cout << "Error: Student with ID " << studentID << " does not exist." << endl;
        return;
    }

    // Display available courses
    cout << "Available Courses:" << endl;
    for (const auto& entry : coursesMap) {
        cout << entry.second.courseCode << " - " << entry.second.courseName << endl;
    }

    int numCourses;
    cout << "Enter the number of courses you want to enroll in: ";
    cin >> numCourses;

    cout << "Enter course codes:" << endl;
    for (int i = 0; i < numCourses; ++i) {
        string courseCode;
        cin >> courseCode;


        if (coursesMap.find(courseCode) == coursesMap.end()) {
            cout << "Error: Course with code " << courseCode << " does not exist." << endl;
            continue;
        }

        // Enroll student in course
        studentsMap[studentID].enrollCourse(&coursesMap[courseCode]);
    }
}

void dropCourseForStudent() {
    string studentID;
    cout << "Enter student ID: ";
    cin >> studentID;


    if (studentsMap.find(studentID) == studentsMap.end()) {
        cout << "Error: Student with ID " << studentID << " does not exist." << endl;
        return;
    }

    studentsMap[studentID].viewCourses();

    string courseCode;
    cout << "Enter the course code you want to drop: ";
    cin >> courseCode;


    if (coursesMap.find(courseCode) == coursesMap.end()) {
        cout << "Error: Course with code " << courseCode << " does not exist." << endl;
        return;
    }


    studentsMap[studentID].dropCourse(&coursesMap[courseCode]);
}

int main() {

    ifstream infile_students("E:\\university\\cp lab\\programs\\oop oelab\\students.txt");
    if (infile_students.is_open()) {

        while (!infile_students.eof()) {
            Student student;
            student.readFromFile(infile_students);
            studentsMap[student.studentID] = student;
        }
        infile_students.close();
    }
    else {
        cerr << "Error: Unable to open students file." << endl;
        return 1;
    }

    // Repeat similar steps for teachers and courses files
    ifstream infile_teachers("E:\\university\\cp lab\\programs\\oop oelab\\teachers.txt");
    if (infile_teachers.is_open()) {
        // Read teacher data from file
        while (!infile_teachers.eof()) {
            Teacher teacher;
            teacher.readFromFile(infile_teachers);
            teachersMap[teacher.teacherID] = teacher;
        }
        infile_teachers.close();
    }
    else {
        cerr << "Error: Unable to open teachers file." << endl;
        return 1;
    }

    ifstream infile_courses("E:\\university\\cp lab\\programs\\oop oelab\\courses.txt");
    if (infile_courses.is_open()) {
        // Read course data from file
        while (!infile_courses.eof()) {
            Course course;
            course.readFromFile(infile_courses);
            coursesMap[course.courseCode] = course;
        }
        infile_courses.close();
    }
    else {
        cerr << "Error: Unable to open courses file." << endl;
        return 1;
    }

    // Use the data read from files to perform operations

    // User interaction
    int choice;
    cout << "1. Enroll a student in course(s)" << endl;
    cout << "2. Drop a course for a student" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        enrollStudentInCourse();
        break;
    case 2:
        dropCourseForStudent();
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }

    return 0;
}


