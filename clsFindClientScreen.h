#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h";

class clsFindClientScreen : protected clsScreen
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

	static void FindClient()
	{
		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pFindClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber = "";

		cout << "Enter Account Number: ";

		AccountNumber = clsInputValidate::ReadString();

		while(!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\n\nNot found Client with Account Number [" << AccountNumber << "] :-(\n";
			cout << "Enter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		
		if (Client.IsEmpty())
		{
			cout << "\nClient Not Found :-(";
		}
		else
		{
			_PrintClient(Client);
		}
	}

};

