#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListClientScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeletClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsMangeUserScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"

class clsMainScreen : protected clsScreen
{
	
private:

	enum enMainMenueOption{ eListClient = 1, eAddClient = 2, eUpdateClient = 3, 
		eDeleteClient = 4, eFindClient = 5, eTransactionMenue = 6, eManageUser = 7, eLoginRegister = 8, eLogOut = 9 };
	
	static enMainMenueOption _ReadMainMenueOption()
	{
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 9);

		return enMainMenueOption(Choice);
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\n\t\tPress any key to go to Main Menue...";
		system("pause > 0");
		ShowMainMenue();
	}

	static void _ListClient()
	{
		//cout << "Client List will be here...";

		clsListClientScreen::ListClient();
	}

	static void _AddClient()
	{
		//cout << "Add Client Will be Here...";

		clsAddNewClientScreen::AddNewClient();
	}

	static void _UpdateClient()
	{
		//cout << "Update Client will be here...";
		clsUpdateClientScreen::UpdateClient();
	}

	static void _DeleteClient()
	{
		//cout << "Delete Client Will be Here...";
		clsDeletClientScreen::DeletClient();
	}

	static void _FindClilent()
	{	
		//cout << "Find Client Will be Here...";

		clsFindClientScreen::FindClient();
	}

	static void _TransactionMenue()
	{
		//cout << "Transaction Menue Will be Here...";
		clsTransactionScreen::ShowTransactionMenue();
	}

	static void _ManageUser()
	{
		// cout << "Manage User Menue Will be Here...";
		clsMangeUserScreen::ShowManageUserScreen();
	}

	static void _LoginRegister()
	{
		//cout << "login Register will be here";
		clsLoginRegisterScreen::LoginRegisterList();
	}

	static void _LogOut()
	{
		CurrentUser = clsBankUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOption Choice)
	{
		switch (Choice)
		{
		case enMainMenueOption::eListClient:
		{
			system("cls");
			_ListClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eAddClient:
		{
			system("cls");
			_AddClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eUpdateClient:
		{
			system("cls");
			_UpdateClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eDeleteClient:
		{
			system("cls");
			_DeleteClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eFindClient:
		{
			system("cls");
			_FindClilent();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eTransactionMenue:
		{
			system("cls");
			_TransactionMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eManageUser:
		{
			system("cls");
			_ManageUser();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOption::eLoginRegister:
		{
			system("cls");
			_LoginRegister();
			_GoBackToMainMenue();
		}
		case enMainMenueOption::eLogOut:
		{
			system("cls");
			_LogOut();
			break;
		}

		}
	}

public:

	static void ShowMainMenue()
	{
		system("cls");

		clsScreen::_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t\tMain Menue\n";
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "[1] Show Client List\n";
		cout << setw(37) << left << "" << "[2] Add New Client\n";
		cout << setw(37) << left << "" << "[3] Update Client\n";
		cout << setw(37) << left << "" << "[4] Delete Client\n";
		cout << setw(37) << left << "" << "[5] Find Client\n";
		cout << setw(37) << left << "" << "[6] Transaction\n";
		cout << setw(37) << left << "" << "[7] Manage User\n";
		cout << setw(37) << left << "" << "[8] Login Register\n";
		cout << setw(37) << left << "" << "[9] Log Out\n";
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "Enter Your Choice [1 to 9]? ";
		
		_PerformMainMenueOption(_ReadMainMenueOption());
	}

};

