#include <iostream>
#include "Instructor.h"

Instructor::Instructor(){

}

void Instructor::setOffice(string new_office)
{
	office = new_office;
}

void Instructor::setDepartment(string new_department)
{
	department = new_department;
}

string Instructor::getOffice()
{
	return office;
}

string Instructor::getDepartment()
{
	return department;
}
