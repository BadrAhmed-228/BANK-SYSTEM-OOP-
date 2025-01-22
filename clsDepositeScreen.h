#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositeScreen : protected clsScreen
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

	static void Deposite()
	{
		clsScreen::_DrawScreenHeader("\t\tDeposite Screen");

		string AccountNumber;

		cout << "Enter Account Number: ";

		AccountNumber = clsInputValidate::ReadString();
		
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount = 0;

		cout << "\nEnter Deposite Amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		char yn = 'y';

		cout << "Are you sure you want to make this transaction Y/N ? ";
		cin >> yn;

		if (tolower(yn) == 'y')
		{
			Client.Deposite(Amount);
			cout << "\n\nDeposite Done Successfully your Balance is: " << Client.AccountBalance;
		}
		else
		{
			cout << "Deposite Canceld...";
		}
	}
};

