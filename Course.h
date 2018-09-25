#ifndef COURSE_H_
#define COURSE_H_

#include <string>
using namespace std;

class Course
{
public:
    Course();
	Course(int new_courseID, string new_courseName);

	void setCourseID(int new_courseID);
	void setCourseName(string new_courseName);

	int getCourseID();
	string getCourseName();
private:
	int courseID;
	string courseName;
};

#endif
