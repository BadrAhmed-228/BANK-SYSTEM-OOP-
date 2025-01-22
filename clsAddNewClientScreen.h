#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsAddNewClientScreen : protected clsScreen
{

private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "Enter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "Enter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "Enter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "Enter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "Enter Balance: ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();
	}

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

	static void AddNewClient()
	{
		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pAddNnewClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("\tAdd New Client Screen");

		string AccountNumber = "";

		cout << "\nEnter Account Number: ";

		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number [" << AccountNumber << "] is already exist Enter another one : ";

			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResults;

		SaveResults = NewClient.Save();

		switch (SaveResults)
		{
		case clsBankClient::enSaveResults::svFailAccountNumberExists:
		{
			cout << "\nError Account Number is already exist";
			break;
		}

		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\n\nClient Added Successfully...\n\n";
			_PrintClient(NewClient);
			break;
		}

		case clsBankClient::enSaveResults::svFailEmptyObject:
		{
			cout << "\n\nError Empty object.";
		}

		}
	}

};

