#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include <iomanip>
#include "Global.h"

class clsLoginRegisterScreen : protected clsScreen
{

public:

	static void LoginRegisterList()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pLoginRegister))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("\tLogin Registerations");

		vector<clsBankUser::stRegisterLogin> vRegisrations = clsBankUser::GetRegisterations();

		cout << "\n\t\t---------------------------------------------------------------------------------------------\n";
		cout << setw(16) << left << "" << "| " << setw(25) << left << "Date-Time";
		cout << "| " << setw(25) << left << "User Name";
		cout << "| " << setw(15) << left << "Password";
		cout << "| " << setw(15) << left << "Permissions";
		cout << "\n\t\t---------------------------------------------------------------------------------------------\n\n";

		if (vRegisrations.size() == 0)
		{
			cout << "\t\tNo Registrations yet";
		}
		else
		{
			for (clsBankUser::stRegisterLogin L : vRegisrations)
			{
				cout << setw(16) << left << "" << "| " << setw(25) << left << L.stDate;
				cout << "| " << setw(25) << left << L.stUserName;
				cout << "| " << setw(15) << left << L.stUserName;
				cout << "| " << setw(15) << left << L.stPermissions;

				cout << "\n";
			}
		}

		cout << "\n\n\t\t---------------------------------------------------------------------------------------------\n";
	}
};

