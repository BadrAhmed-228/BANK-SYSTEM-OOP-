#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsMangeUserScreen : protected clsScreen
{

private:

	enum enManageUserMenue { eListUser = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 };

	static enManageUserMenue _ReadManageUserMenueOption()
	{
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6);

		return enManageUserMenue(Choice);
	}

	static void _GoBackToManageUserMenue()
	{
		cout << "\n\n\t\tPress Any key to go to User Manage Menue...";
		system("Pause > 0");
		ShowManageUserScreen();
	}

	static void _ListUser()
	{
		//cout << "List User Screen will be here...";
		clsListUserScreen::ListScreen();
	}

	static void _AddNewUser()
	{
		//cout << "Add New User Screen will be here...";
		clsAddNewUserScreen::AddNewUser();
	}

	static void _DeleteUser()
	{
		//cout << "Delete User Screen will be here...";
		clsDeleteUserScreen::DeleteUser();
	}

	static void _UpdateUser()
	{
		//cout << "Update User Screen will be here...";
		clsUpdateUserScreen::UpdateUser();
	}

	static void _FindUser()
	{
		//cout << "Find User Screen will be here...";
		clsFindUserScreen::FindUser();
	}

	static void _PerformManageUserMenueOption(enManageUserMenue Choice)
	{
		switch (Choice)
		{
		case clsMangeUserScreen::eListUser:
		{
			system("cls");
			_ListUser();
			_GoBackToManageUserMenue();
			break;
		}
		case clsMangeUserScreen::eAddNewUser:
		{
			system("cls");
			_AddNewUser();
			_GoBackToManageUserMenue();
			break;
		}
		case clsMangeUserScreen::eDeleteUser:
		{
			system("cls");
			_DeleteUser();
			_GoBackToManageUserMenue();
			break;
		}
		case clsMangeUserScreen::eUpdateUser:
		{
			system("cls");
			_UpdateUser();
			_GoBackToManageUserMenue();
			break;
		}
		case clsMangeUserScreen::eFindUser:
		{
			system("cls");
			_FindUser();
			_GoBackToManageUserMenue();
			break;
		}
		case clsMangeUserScreen::eMainMenue:
		{
			// do nothing
		}
		
		}
	}
	
public:

	static void ShowManageUserScreen()
	{
		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pManageUser))
		{
			return;
		}

		system("cls");

		clsScreen::_DrawScreenHeader("\t Manage User Screen");

		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t\t Manage User Menue\n";
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t[1] Users List\n";
		cout << setw(37) << left << "" << "\t[2] Add New User\n";
		cout << setw(37) << left << "" << "\t[3] Delete User\n";
		cout << setw(37) << left << "" << "\t[4] Update User\n";
		cout << setw(37) << left << "" << "\t[5] Find User\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue\n";
		cout << setw(37) << left << "" << "====================================================\n";

		cout << setw(37) << left << "" << "Enter Your choice [1 to 6]: ";

		_PerformManageUserMenueOption(_ReadManageUserMenueOption());
	}

};

