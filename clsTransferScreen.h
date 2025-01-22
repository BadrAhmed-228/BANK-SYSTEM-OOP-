#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientInfo(clsBankClient Client)
	{
		cout << "---------------------------------------------------------\n";
		cout << "Acc.Number: " << Client.AccountNumber() << endl;
		cout << "Full Name : " << Client.FullName() << endl;
		cout << "Balance   : " << Client.AccountBalance << endl;
		cout << "---------------------------------------------------------";
	}

	static string _ReadAccountNumber(string status)
	{
		string Acc;

		cout << "\nEnter Account Number to transfer " <<  status << ": ";
		Acc = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(Acc))
		{
			cout << "\nAccount Number is not exist enter another one: ";
			Acc = clsInputValidate::ReadString();
		}

		return Acc;
	}

public:

	static void Transfer()
	{
		clsScreen::_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient Client1 = clsBankClient::Find(_ReadAccountNumber("from"));

		cout << "\nClient 1 Card:\n";
		_PrintClientInfo(Client1);

		clsBankClient Client2 = clsBankClient::Find(_ReadAccountNumber("to"));

		cout << "\n\nClient 2 Card:\n";
		_PrintClientInfo(Client2);

		cout << "\nEnter Amount to transfer: ";
		double Amount = clsInputValidate::ReadDblNumber();

		char yn = 'y';

		cout << "\nAre you sure you want to make this transaction Y/N ? ";
		cin >> yn;

		if (tolower(yn) != 'y')
		{
			return;
		}

		while (!Client1.Transfer(Amount, Client2, CurrentUser.UserName()))
		{
			cout << "\nAmount Exeeds the balance you can transfer up to " << Client1.AccountBalance;
			cout << "Enter Amount to transfer: ";

			Amount = clsInputValidate::ReadDblNumber();

			cout << "\nAre you sure you want to make this transaction Y/N ? ";
			cin >> yn;

			if (tolower(yn) != 'y')
			{
				return;
			}
		}

		cout << "\n\nTransaction done successfully...\n";
	}

};

