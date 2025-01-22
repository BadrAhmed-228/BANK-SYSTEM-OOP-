#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:

	static void _PrintUser(clsBankUser User)
	{
		cout << "\nUser Info: \n";
		cout << "-------------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName();
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-------------------------------";
	}

public:

	static void DeleteUser()
	{
        clsScreen::_DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";

        UserName = clsInputValidate::ReadString();

        while (!(clsBankUser::IsUserExist(UserName)))
        {
            cout << "\nUser Name not found Enter another one: ";

            UserName = clsInputValidate::ReadString();
        }

        clsBankUser User = clsBankUser::Find(UserName);
        _PrintUser(User);

        cout << "\n\nAre you sure you want to delete this User y/n ? ";

        char yn = 'n';
        cin >> yn;

        if (tolower(yn) == 'y')
        {
            if (User.Delete())
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

