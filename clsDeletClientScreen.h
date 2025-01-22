#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDeletClientScreen : protected clsScreen
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
	
	static void DeletClient()
	{
        if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pDeleteClient))
        {
            return;
        }

        clsScreen::_DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";

        AccountNumber = clsInputValidate::ReadString();

        while (!(clsBankClient::IsClientExist(AccountNumber)))
        {
            cout << "\nAccount Number not found Enter another one: ";

            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\n\nAre you sure you want to delete this client y/n ? ";

        char yn = 'n';
        cin >> yn;

        if (tolower(yn) == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully...";
            }
            else
            {
                cout << "\nError Client is not Deleted :-(";
            }
        }
	}
};

