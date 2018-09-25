#include <iostream>
#include "Course.h"

Course::Course(int new_courseID, string new_courseName)
{
	courseID = new_courseID;
	courseName = new_courseName;
}

Course::Course(){

}

void Course::setCourseID(int new_courseID)
{
	courseID = new_courseID;
}

void Course::setCourseName(string new_courseName)
{
	courseName = new_courseName;
}

int Course::getCourseID()
{
	return courseID;
}

string Course::getCourseName()
{
	return courseName;
}
