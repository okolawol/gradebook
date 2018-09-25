#include <iostream>
#include "Student.h"



Student::Student(){

}

void Student::setDepartment(string new_department)
{
	department = new_department;
}

void Student::setMajor(string new_major)
{
	major = new_major;
}

string Student::getDepartment()
{
	return department;
}

string Student::getMajor()
{
	return major;
}
