#pragma once

#include <iostream>
#include <string>

using namespace std; // A7a dih ely kanet mwa2fa 2l bernameg w gaybaly 51 errors

class clsPerson
{

private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		this->_FirstName = FirstName;
		this->_LastName = LastName;
		this->_Email = Email;
		this->_Phone = Phone;
	}

	void SetFirstName(string FirstName)
	{
		this->_FirstName = FirstName;
	}

	string GetFirstName()
	{
		return this->_FirstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		this->_LastName = LastName;
	}

	string GetLastName()
	{
		return this->_LastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	void SetEmail(string Email)
	{
		this->_Email = Email;
	}

	string GetEmail()
	{
		return this->_Email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone)
	{
		this->_Phone = Phone;
	}

	string GetPhone()
	{
		return this->_Phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

};

