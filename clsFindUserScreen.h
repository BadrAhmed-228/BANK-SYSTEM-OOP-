#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{

private:

	static void _PrintUser(clsBankUser User)
	{
		cout << "\nUser Info: \n";
		cout << "-------------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName();
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-------------------------------";
	}

public:

	static void FindUser()
	{
		clsScreen::_DrawScreenHeader("\tFind User Screen");

		string UserName = "";

		cout << "Enter User Name: ";

		UserName = clsInputValidate::ReadString();

		while (!(clsBankUser::IsUserExist(UserName)))
		{
			cout << "\n\nNot found User with User Name [" << UserName << "] :-(\n";
			cout << "Enter User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsBankUser User = clsBankUser::Find(UserName);

		if (User.IsEmpty())
		{
			cout << "\nClient Not Found :-(";
		}
		else
		{
			_PrintUser(User);
		}
	}

};

