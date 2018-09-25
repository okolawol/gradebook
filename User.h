#ifndef USER_H_
#define USER_H_

#include <string>
#include "Account.h"

class User
{
public:
    User();
	void setID(string new_id);
	void setAccount(string username, string password);
	void setAccount(Account new_account);
	void setUserType(string new_userType);
	void setFirstName(string new_firstName);
	void setLastName(string new_lastName);
	void setEmail(string new_email);
	
	string getID();
    Account getAccount();
	string getUserType();
	string getFirstName();
	string getLastName();
	string getEmail();

	~User();

private:
	string id;
    Account account;
	string userType;
	string firstName;
	string lastName;
	string email;
};

#endif
