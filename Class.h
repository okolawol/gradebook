#ifndef CLASS_H
#define CLASS_H

#include "Grade.h"
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include "Student.h"
#include "TA.h"
#include "Instructor.h"
#include "databaseif.h"
#include "Semester.h"

class Class {
private:
	vector<Student> students; //needs to be sorted in alphabetical order
	vector<TA> TAs;
	Instructor instructor;
	Semester semester;
	string className; //e.g. CMPT 102, CHEM 303, etc.
	string classSection;
	int classID;
	int courseID;
    int semesterID;
    bool letterGradeReleased;
    vector<double> letterGradeRange;
    DatabaseIF* db;

public:
    Class();
    Class (int newClassID, string newClassSection, int newCourseID, int newSemesterID, DatabaseIF* db);
	~Class();
    void setClassID(int new_ClassID);
    void setInstructor(Instructor new_instructor);
	void addStudent(Student student);
	void removeStudent(int studentID);
	void addTA(TA ta);
    vector<TA> getTAs();
	void removeTA(int TANum);
	int getClassID();
    int getCourseID();
    void setCourseID(int newID);
    string getClassSection();
    void setClassSection(string newSection);

    void addActivity(string activity, double weight, double maxMark);
    void deleteActivity(int activityID);
    void updateActivity(int activityID, int classId, string activity, double maxMark, double weight);

	Instructor getInstructor();
    Student getStudent(string studentID); //retrieve information on one student
	vector<Student> getStudents(); //retrieve information on all students
	void setSemester(Semester new_semester);
	Semester getSemester();
    int getSemesterID();
	void setClassName(string new_className);
	string getClassName();
    void setGrade(string studentID, int activityID, double mark);
	Grade getGrade(int studentID);
    bool getLetterGradeReleased();
    void setLetterGradeReleased(bool newLetterGradeReleased);

    vector<double> getLetterGradeRange();
    bool updateLetterGradeRangeOnDB(vector<double> newLetterGradeRange);


};

#endif


/*
	Constructor takes (classID, classSection, courseID, SemesterCode)
	
	1xxy
		xx = year, 13 14 15
		y = semester, 1 spring, 4 summer, 7 winter

*/
