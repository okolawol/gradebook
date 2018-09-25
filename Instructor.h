#ifndef INSTRUCTOR_H_
#define INSTRUCTOR_H_

#include <string>
#include "User.h"
using namespace std;

class Instructor : public User
{
public:
    Instructor();
	void setOffice(string new_office);
	void setDepartment(string new_department);
	string getOffice();
	string getDepartment();
private:
	string office;
	string department;
};

#endif
