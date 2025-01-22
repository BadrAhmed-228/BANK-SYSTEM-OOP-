#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsUpdateClientScreen : protected clsScreen
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

public:

	static void UpdateClient()
	{
		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pUpdateClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";
		
		cout << "Please Enter Account Number: ";
		
	    AccountNumber = clsInputValidate::ReadString();
		
	    while (!(clsBankClient::IsClientExist(AccountNumber)))
	    {
	        cout << "\nAccount Number [" << AccountNumber << "] is not found, Enter another one: ";
	        AccountNumber = clsInputValidate::ReadString();
	    }
		
	    clsBankClient Client = clsBankClient::Find(AccountNumber);
		
	    _PrintClient(Client);

		char yn = 'n';

		cout << "\n\nAre you sure you want to update this client Y/N ? ";
		cin >> yn;

		if (tolower(yn) != 'y')
		{
			return;
		}
		
        cout << "\n\nUpdate Client:\n";
	    cout << "-----------------------------\n";
	    
	    _ReadClientInfo(Client);
	    
	    cout << "\n-----------------------------";
	
	    if (Client.Save() == clsBankClient::enSaveResults::svFailEmptyObject)
	    {
	        cout << "\n\nEmpty Object :-(";
	    }
	    else
	    {
	        cout << "\n\nSaved successfully :-)";
	    }
	}

};

