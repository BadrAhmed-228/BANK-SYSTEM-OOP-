#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "iomanip"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsShowTransferLogScreen.h"

class clsTransactionScreen : protected clsScreen
{

private:

	enum enTransactionMenueOption{ eDeposite = 1, eWithdraw = 2, eShowTotaalBalances = 3, eTransfer = 4, eShowTransferLog = 5, eShowMainMenue = 6 };

	static enTransactionMenueOption _ReadTransactionMenueOption()
	{
		short Choice = 0;

		Choice = clsInputValidate::ReadIntNumberBetween(1, 6);

		return enTransactionMenueOption(Choice);
	}

	static void _GoBackToTransactionMenue()
	{
		cout << "\n\n\t\tPress Any key to go back to Transaction Menue...";
		system("pause > 0");
		ShowTransactionMenue();
	}

	static void _Depsite()
	{
		 //cout << "Deposite will be here...";
		clsDepositeScreen::Deposite();
	}

	static void _Withdraw() 
	{
		//cout << "Withdraw screen will be here";
		clsWithdrawScreen::Withdraw();
	}

	static void _ShowTotalBalances()
	{
		//cout << "Total Balances Screen will be Here";
		clsTotalBalancesScreen::TotalBalances();
	}

	static void _Transfer()
	{
		//cout << "transfere screen will be here";
		clsTransferScreen::Transfer();
	}

	static void _ShowTransferLog()
	{
		//show transfer Log screen will be here
		clsShowTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionMenueOption(enTransactionMenueOption TransactionMenueOption)
	{
		switch (TransactionMenueOption)
		{
		case enTransactionMenueOption::eDeposite:
		{
			system("cls");
			_Depsite();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionMenueOption::eWithdraw:
		{
			system("cls");
			_Withdraw();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionMenueOption::eShowTotaalBalances:
		{
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionMenueOption::eTransfer:
		{
			system("cls");
			_Transfer();
			_GoBackToTransactionMenue();
			break;
		}

		case enTransactionMenueOption::eShowTransferLog:
		{
			system("cls");
			_ShowTransferLog();
			_GoBackToTransactionMenue();
			break;
		}

		case enTransactionMenueOption::eShowMainMenue:
		{
			//do Nothing here the mainScreen will handel it...
		}

		}
	}

public:

	static void ShowTransactionMenue()
	{
		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pTransactions))
		{
			return;
		}

		system("cls");

		clsScreen::_DrawScreenHeader("\tTransactions Screen");

		cout << setw(37) << left << "" << "==========================================\n";
		cout << setw(37) << left << "" << "\t  Transaction Menue\n";
		cout << setw(37) << left << "" << "==========================================\n";
		cout << setw(37) << left << "" << "\t[1] Depsite\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances\n";
		cout << setw(37) << left << "" << "\t[4] Transfer\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Logs\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";

		cout << setw(37) << left << "" << "Choose Transaction [1 to 6] ? ";

		_PerformTransactionMenueOption(_ReadTransactionMenueOption());
	}

};

