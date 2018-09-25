#ifndef TA_H_
#define TA_H_

#include <string>
#include "User.h"
using namespace std;

class TA : public User
{
public:
    TA();
	void setOffice(string new_office);
	string getOffice();
private:
	string office;
};

#endif
