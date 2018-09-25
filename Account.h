#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
using namespace std;

class Account
{
public:
    Account();
	Account(string new_username, string new_password);
	void setUsername(string new_username);
	void setPassword(string new_password);
	string getUsername();
	string getPassword();
private:
	string username;
	string password;
};

#endif
