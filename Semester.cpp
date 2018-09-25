#include <iostream>
#include "Semester.h"



Semester::Semester(){

}

void Semester::setSemesterID(int new_semesterID)
{
	semesterID = new_semesterID;
}

void Semester::setYear(int new_year)
{
	year = new_year;
}

void Semester::setTerm(string new_term)
{
	term = new_term;
}

int Semester::getSemesterID()
{
	return semesterID;
}

int Semester::getYear()
{
	return year;
}

string Semester::getTerm()
{
	return term;
}
