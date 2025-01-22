#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsMainScreen.h"
#include <fstream>
#include "clsDate.h"

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login()
	{
		string UserName = "";
		string Password = "";

		bool LoginFail = false;

		short counter = 3;

		do
		{
			if (LoginFail && --counter > 0) 
			{
				cout << "\nInvalid User Name or Password Please try again\n";
				cout << "You have " << counter << " trials befor lock system\n";
			}

			if (counter == 0)
			{
				cout << "\nYou locked out :-(\n";
				return false;
			}

			cout << "\nEnter User Name: ";
			UserName = clsInputValidate::ReadString();

			cout << "\nEnter Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsBankUser::Find(UserName, Password);

			LoginFail = CurrentUser.IsEmpty();

		} while (LoginFail && counter > 0);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenue();
		
		return true;
	}

public:

	static bool Login()
	{
		system("cls");

		clsScreen::_DrawScreenHeader("\t  Login Screen");

		return _Login();
	}

};

