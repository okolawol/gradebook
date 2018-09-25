#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include "User.h"
using namespace std;

class Student : public User
{
public:
    Student();
	void setDepartment(string new_department);
	void setMajor(string new_major);
	string getDepartment();
	string getMajor();
private:
	string department;
	string major;
};

#endif
