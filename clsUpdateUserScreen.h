#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{

private:

	static int _ReadPermissions()
	{
		int Permissions = 0;

		char YN = 'y';

		cout << "\nDo you want to give full access Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n";

		cout << "\nShow client list Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pListClient;
		}

		cout << "\nAdd new client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pAddNnewClient;
		}

		cout << "\nUpdate client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pUpdateClient;
		}

		cout << "\nDelete client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pDeleteClient;
		}

		cout << "\nFind client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pManageUser;
		}

		cout << "\nRegister Login YN ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

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

	static void _ReadUserInfo(clsBankUser& User)
	{
		cout << "Enter First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "Enter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "Enter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "Enter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "Enter Permissions: ";
		User.Permissions = _ReadPermissions();
	}

public:

	static void UpdateUser()
	{
		clsScreen::_DrawScreenHeader("\tUpdate User Screen");

		string UserName;
		
		cout << "\nEnter User Name: ";
		
		UserName = clsInputValidate::ReadString();

		while (!clsBankUser::IsUserExist(UserName))
		{
			cout << "\nUser with User Name [" << UserName << "] is not exist";
			cout << "Enter another User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsBankUser User = clsBankUser::Find(UserName);

		_PrintUser(User);

		char yn = 'y';

		cout << "\n\nAre you sure you want to update this user Y/N ? ";
		cin >> yn;

		if (tolower(yn) != 'y')
		{
			return;
		}

		cout << "\n\nUpdate User: \n";

		cout << "--------------------------------------------\n";

		_ReadUserInfo(User);

		cout << "\n--------------------------------------------\n";

		if (User.Save() == clsBankUser::enSaveResults::svFailEmptyObject)
		{
			cout << "\n\nSave fail empty object";
		}
		else
		{
			cout << "\n\nUser Updated successfully...";
		}

	}

};

