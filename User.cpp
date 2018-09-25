#include <iostream>
#include "User.h"

User::~User()
{
    //delete account;
}
User::User(){

}

void User::setID(string new_id)
{
	id = new_id;
}

void User::setAccount(string username, string password)
{
    account = Account(username, password);
}

void User::setAccount(Account new_account)
{
    account = new_account;
}

void User::setUserType(string new_userType)
{
	userType = new_userType;
}

void User::setFirstName(string new_firstName)
{
	firstName = new_firstName;
}

void User::setLastName(string new_lastName)
{
	lastName = new_lastName;
}

void User::setEmail(string new_email)
{
	email = new_email;
}

string User::getID()
{
	return id;
}

Account User::getAccount()
{
    return account;
}

string User::getUserType()
{
	return userType;
}

string User::getFirstName()
{
	return firstName;
}

string User::getLastName()
{
	return lastName;
}

string User::getEmail()
{
	return email;
}
