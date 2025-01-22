#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card: \n";
		cout << "-------------------------------";
		cout << "\nFirst Name  : " << Client.FirstName;
		cout << "\nLast Name   : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPinCode     : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n-------------------------------";
	}

public:

	static void Withdraw()
	{
		clsScreen::_DrawScreenHeader("\t\tWithdraw Screen");

		string AccountNumber;
		
		cout << "Enter Account Number: ";

		AccountNumber = clsInputValidate::ReadString();

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount = 0;

		cout << "\nEnter Amount to withdraw: ";
		Amount = clsInputValidate::ReadDblNumber();

		char yn = 'y';

		cout << "\nAre you sure you want to withdraw Y/N ? ";
		cin >> yn;

		if (tolower(yn) == 'y')
		{
			while (!(Client.Withdraw(Amount)))
			{
				cout << "\n\nAmount exceeds the Balance you can withdraw up to " << Client.AccountBalance;
				cout << "\nEnter Amount to Withdraw: ";
				Amount = clsInputValidate::ReadDblNumber();
			}
			
			cout << "\n\nWithdraw done successfully your Balance is: " << Client.AccountBalance;
		}
		else
		{
			cout << "\n\nWithdraw Canceld...";
		}
	}

};