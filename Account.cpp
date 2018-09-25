#include <iostream>
#include "Account.h"


Account::Account(){

}

Account::Account(string new_username, string new_password)
{
	username = new_username;
	password = new_password;
}

void Account::setUsername(string new_username)
{
	username = new_username;
}

void Account::setPassword(string new_password)
{
	password = new_password;
}

string Account::getUsername()
{
	return username;
}

string Account::getPassword()
{
	return password;
}
