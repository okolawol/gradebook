#ifndef SEMESTER_H_
#define SEMESTER_H_

#include <string>
using namespace std;

class Semester
{
public:
    Semester();
	void setSemesterID(int new_semesterID);
	void setYear(int new_year);
	void setTerm(string new_term);

	int getSemesterID();
	int getYear();
	string getTerm();
private:
	int semesterID;
	int year;
	string term;
};

#endif
