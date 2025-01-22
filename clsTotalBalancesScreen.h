#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTotalBalancesScreen : protected clsScreen
{

public:

	static void TotalBalances()
	{
		clsScreen::_DrawScreenHeader("\tTotal Balances");

		vector<clsBankClient> vClients = clsBankClient::GetClientList();

		cout << "\n\t\t-----------------------------------------------------------------------------\n";
		cout << setw(16) << left << "" << "| " << setw(20) << left << "Acc. Number";
		cout << "| " << setw(30) << left << "Full Name";
		cout << "| " << setw(15) << left << "Balance";
		cout << "\n\t\t-----------------------------------------------------------------------------\n\n";

		if (vClients.size() == 0)
		{
			cout << "\t\tNo Clients Available to show";
		}
		else
		{
			for (clsBankClient C : vClients)
			{
				cout << setw(16) << left << "" << "| " << setw(20) << left << C.AccountNumber();
				cout << "| " << setw(30) << left << C.FullName();
				cout << "| " << setw(15) << left << C.AccountBalance;

				cout << "\n";
			}
		}

		cout << "\n\n\t\t-----------------------------------------------------------------------------\n";

		cout << "\n\t\t\t\tTotal Balances: " << clsBankClient::GetTotalBalances() << endl;
	}
};

